use std::env;
use std::fs::File;
use std::io::{BufRead, BufReader};
use rand::Rng;

const MAX_BUF_SIZE: usize = 256;

fn gcd(a: u64, b: u64) -> u64 {
    let mut a = a;
    let mut b = b;
    while b != 0 {
        let temp = b;
        b = a % b;
        a = temp;
    }
    a
}

fn mod_pow(base: u64, exponent: u64, modulus: u64) -> u64 {
    let mut result = 1;
    let mut base = base % modulus;
    let mut exponent = exponent;
    while exponent > 0 {
        if exponent & 1 == 1 {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent >>= 1;
    }
    result
}

fn is_prime(n: u64) -> bool {
    if n == 2 || n == 3 {
        return true;
    } else if n <= 1 || n % 2 == 0 || n % 3 == 0 {
        return false;
    }
    let mut i = 5;
    while i * i <= n {
        if n % i == 0 || n % (i + 2) == 0 {
            return false;
        }
        i += 6;
    }
    true
}

fn rsa(filename: &str) -> Result<(), std::io::Error> {
    let file = File::open(filename)?;
    let reader = BufReader::new(file);
    for line in reader.lines() {
        let n = line?.trim().parse::<u64>().unwrap();
        let mut rng = rand::thread_rng();
        let p: u64 = loop {
            let candidate = rng.gen_range(1, n);
            if is_prime(candidate) {
                break candidate;
            }
        };
        let mut q: u64 = loop {
            let candidate = rng.gen_range(1, n);
            if is_prime(candidate) && candidate != p {
                break candidate;
            }
        };
        let phi = (p - 1) * (q - 1);
        let e = 65537;
        let mut d = 0;
        loop {
            if gcd(e, phi) == 1 {
                d = mod_pow(e, phi - 1, phi);
                break;
            }
            e += 1;
        }
        println!("{}={}{}", n, p, q);
    }
    Ok(())
}

fn main() -> Result<(), std::io::Error> {
    let args: Vec<String> = env::args().collect();
    if args.len() != 2 {
        println!("Usage: {} <filename>", args[0]);
        return Ok(());
    }
    let filename = &args[1];
    rsa(filename)?;
    Ok(())
}
