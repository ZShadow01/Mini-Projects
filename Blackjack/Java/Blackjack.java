import java.util.Random;
import java.util.ArrayList;
import java.util.Scanner;


public class Blackjack {
    public static final int decks = 8;
    public static final int winningScore = 21;

    private Hand player;
    private Hand dealer;
    private ArrayList<Card> currentStack;

    public Blackjack() {
        /*
         * Prepare all cards that will be played and the player and dealer
         * Blackjack is usually played with one to eight decks of cards
         */
        this.currentStack = new ArrayList<>();

        CardType[] cards = CardType.values();
        for (int i = 0; i < Blackjack.decks * 4 * cards.length; i++) {
            this.currentStack.add(new Card(cards[i % cards.length]));
        }

        this.player = new Hand();
        this.dealer = new Hand();
    }

    private void shuffleCurrentStack() {
        /*
         * Iterate through the stack and swap card objects with a randomly chosen card from the stack
         */
        Random random = new Random();

        for (int i = 0; i < this.currentStack.size(); i++) {
            int x = random.nextInt(this.currentStack.size());
            Card firstCard = this.currentStack.get(i);
            Card secondCard = this.currentStack.get(x);

            this.currentStack.set(i, secondCard);
            this.currentStack.set(x, firstCard);
        }
    }

    private void runPlayer() {
        /*
         * Prompt player until he ends his turn or goes over 21 (BUST)
         * No split, double-downs, etc.
         */
        Scanner scanner = new Scanner(System.in);
        boolean active = true;
        int currentScore;

        System.out.println("Player's turn");
        while ((currentScore = this.player.getScore()) < Blackjack.winningScore && active) {
            System.out.println("Your cards: " + this.player.toString() + " -> " + currentScore);

            System.out.print("HIT or STAND: ");
            String in = scanner.nextLine().toUpperCase();

            if (in.equals("HIT")) {
                this.player.add(this.currentStack.remove(0));
            }
            else if (in.equals("STAND")) {
                active = false;
            }

            System.out.println();
        }

        scanner.close();
    }

    private void runDealer() {
        /* 
         * Dealer has no option -> keep drawing cards until he reaches a score of 17 or more
         */
        while (this.dealer.getScore() < 17) {
            this.dealer.add(this.currentStack.remove(0));
        }
    }

    public void run() {
        // Shuffle the stack
        this.shuffleCurrentStack();

        // Player and dealer receives 2 cards at the start
        this.player.add(this.currentStack.remove(0));
        this.player.add(this.currentStack.remove(0));
        this.dealer.add(this.currentStack.remove(0));
        this.dealer.add(this.currentStack.remove(0));
        
        // Run both player and the dealer
        this.runPlayer();
        this.runDealer();

        // Scoring
        int playerScore = this.player.getScore();
        int dealerScore = this.dealer.getScore();

        System.out.println("Player: " + this.player.toString() + " -> " + playerScore);
        System.out.println("Dealer: " + this.dealer.toString() + " -> " + dealerScore);

        
    }
}
