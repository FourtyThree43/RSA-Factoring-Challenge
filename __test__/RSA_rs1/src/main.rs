use std::env;
use std::fs::File;
use std::io::{BufRead, BufReader};

#[inline]
fn is_prime(n: u128) -> bool{
    if n <= 1{
        false
    }else if n <= 3{
        true
    }else if n % 2 == 0 || n % 3 == 0 {
        false
    }else {
        let mut i =3;
        while i * i <= n{
            if n % i == 0 || n % (i + 2) == 0 {
                return false;
            }
            i += 6;
        }
        true
    }
}

fn find_factor(n: u128)-> u128 {
    let sqrt_n = (n as f64).sqrt() as u128;
    let mut factor = 2;
    while factor <= sqrt_n{
        if n % factor == 0 && is_prime(factor) {
            return  factor;
        }
        factor += 1;
    }
    n
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 2{
        eprintln!("Ussage: factors <file>");
        std::process::exit(1);

    }
    let file = File::open(&args[1]).expect("Error opening file");
    let reader = BufReader::with_capacity(1024 * 1024, file); // 1MB buffer
    reader.lines().for_each(|line| {
        let n = line.unwrap().trim().parse().unwrap();
        let p = find_factor(n);
        let q  = n / p;
        println!("{}={}*{}",n, p, q);
    });
}
