/* Roots.java
 * Usman Zahid
 * uzahid
 * pa4
 * Finds the roots of polynomials in a specified range.
 */
import java.util.*;

class Roots {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		double resolution = .01;
		double tolerance = .0000001;
		double threshold = .001;
		boolean rootfound = false; // set initially to false meaning there are no roots
		double a, b, c, L, R;
		int i;
		int degree;

		System.out.print("Enter the degree: ");
		degree = sc.nextInt();
		double[] C = new double[degree + 1];
		System.out.print("Enter " + (degree + 1) + " coefficients: ");
		for (i = 0; i < C.length; i++) {
			C[i] = sc.nextDouble();
		}
		System.out.print("Enter the left and right endpoints: ");
		L = sc.nextDouble();
		R = sc.nextDouble();
		double[] E = diff(C);
		a = L;
		b = a + resolution;
		while (a < R) {
			if (poly(C, a) * poly(C, b) < 0) {
				double root = findRoot(C, a, b, tolerance);
				System.out.print("Root found at ");
				System.out.printf("%.5f%n", root);
				rootfound = true; // if a root is found, then the boolean value is changed
			}
			if (poly(E, a) * poly(E, b) < 0) {
				double root = findRoot(E, a, b, tolerance);
				if (Math.abs(poly(C, root)) < threshold) {
					System.out.print("Root found at ");
					System.out.printf("%.5f%n", root);
					System.out.print("");
					rootfound = true; // if a root is found then it is changed
				}
			}
			a = b;
			b = a + resolution;
		}
		if (rootfound == false) { //if the above while loop finds no roots, then the boolean remains false and it prints the statement below
			System.out.print("No roots were found in the specified range.");
		}
	}

	// first method: evaluates f(x)
	static double poly(double[] C, double x) {
		double sum = 0;

		for (int i = 0; i < C.length; i++) {
			sum += Math.pow(x, i) * C[i];
		}
		return sum;
	}

	// second method: power rule
	static double[] diff(double[] C) {
		double[] D = new double[C.length - 1];
		for (int i = 1; i <= C.length - 1; i++) {
			D[i - 1] = C[i] * i;
		}
		return D;
	}
	// third method: bisection method
	static double findRoot(double[] C, double a, double b, double tolerance) {
		double root = 0.0, residual, sgn;

		while ((b - a) > tolerance) {
			root = (a + b) / 2.0;
			sgn = Math.signum(poly(C, b) - poly(C, a));
			residual = poly(C, root);
			if (sgn * residual > 0)
				b = root; // replace right endpoint
			else
				a = root; // replace left endpoint
		}
		return root; //returns the value that is found to the accuracy of tolerance
	}
}
