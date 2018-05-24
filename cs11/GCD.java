/* GCD.java
 * Usman Zahid
 * uzahid
 * pa3
 * Takes two positive integer values and gives the greatest common denominator of both.
 */

import java.util.Scanner;

public class GCD {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int b = 0;
		int d = 0;
		int i;
		boolean iError = true;

		System.out.println("Enter a positive integer: ");
		while (iError) {
			if (sc.hasNextInt()) {
				b = sc.nextInt();
			} else {
				System.out.println("Please enter a positive integer: ");
				sc.next();
				continue;
			}
			System.out.println("Enter another positive integer:");
			if (sc.hasNextInt()) {
				d = sc.nextInt();
				System.out.println("The GCD of " + b + " and " + d + " is "
						+ getGcd(b, d) + ".");
			}
			while (!sc.hasNextInt()) {
				System.out.println("Please enter another positive integer: ");
				sc.next();

				if (sc.hasNextInt()) {
					d = sc.nextInt();
					System.out.println("The GCD of " + b + " and " + d + " is "
							+ getGcd(b, d) + ".");
					break;
				}
			}

			iError = false;

		}

		// b = sc.nextInt();

		// if (!sc.hasNextInt())
		// d = sc.nextInt();

	}

	public static int getGcd(int b, int d) {
		int gcd = 1;

		if (b > d) {
			for (int i = d; i >= 1; i--) {
				if (b % i == 0 && d % i == 0) {
					return i;
				}
			}
		} else {
			for (int j = b; j >= 1; j--) {
				if (b % j == 0 && d % j == 0) {
					return j;
				}
			}
		}
		return gcd;

	}
}
