/* Guess.java 
 * Usman Zahid
 * uzahid
 * pa2
 * A guessing game where you have three tries to guess the correct number.
 */

import java.util.Scanner;

public class Guess {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		double number;
		double guess;
		double tries = 1;
		number = (int) (Math.round(Math.random() * 10)); //used Math.round(Math.random()*10) to change the double value to an int
		System.out.println("I'm thinking of an integer in the range 1 to 10. You have three guesses. "); 
		System.out.println("Enter your first guess: ");
		guess = sc.nextInt();
		while (tries <= 3) { //limits the amount of plays to only three tries
			if (guess == number) {
				System.out.println("You win!");
				break; //stops the game if the user wins on any try
			} else if (guess <= number) {
				System.out.println("Your guess was too low ");
				if (tries == 1) {
					System.out.println("Enter your second guess: ");
				} else if (tries == 2) {
					System.out.println("Enter your third guess: ");
				}
				tries = tries + 1; //adds the amount of tries to the game
				guess = sc.nextInt();
			} else if (guess >= number) {
				System.out.println("Your guess was too high ");
				if (tries == 1) {
					System.out.println("Enter your second guess: ");
				} else if (tries == 2) {
					System.out.println("Enter your third guess: ");
				}

				tries = tries + 1;
				guess = sc.nextInt();
			}
			if (tries == 3 && guess!=number) { //the user will lose if by the third try they do not guess the correct number
				System.out.format("You lose! The number was %1.0f", number);
				System.out.println(".");
				break; //stops the game from running at the end

			}

		}
	}

}
