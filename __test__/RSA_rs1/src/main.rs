#![allow(unused)]
use std::env;
use std::fs::{File, read_to_string};
use std::io::{Result, BufRead, BufReader};

#[inline]
fn is_prime(n: u128) -> bool{
    if n == 2 || n == 3{
        return true;
    }else if n <= 1 || n % 2 == 0 || n % 3 == 0 {
        false
    }else {
        let mut i = 5;
        while i * i <= n {
            if n % i == 0 || n % (i + 2) == 0 {
                return false;
            }
            i += 6
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

fn main() -> Result<()> {
    let args: Vec<String> = std::env::args().collect();
    let content = std::fs::read_to_string(&args[1])?;
    content.lines().into_iter().for_each(|line| {
        let n = line.trim().parse().unwrap();
        let p= find_factor(n);
        let q = n / p;
        println!("{}={}*{}", n, p, q);
    });
    Ok(())
}
