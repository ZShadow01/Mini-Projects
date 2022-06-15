import java.util.ArrayList;


public class Hand {
    private ArrayList<Card> cards;

    public Hand() {
        this.cards = new ArrayList<>();
    }

    public void add(Card card) {
        this.cards.add(card);
    }

    public int getScore() {
        /*
         * Sum up the values of each card
         * JACKs, QUEENs and KINGs are worth 10
         * ACEs can be 1 or 11 (player are allowed to choose)
         */
        int score = 0;

        for (Card card : this.cards) {
            score += card.getValue();
            
            // Change ACE value to 1 if score is over 21
            for (int i = 0; i < this.cards.size() && score > Blackjack.winningScore; i++) {
                Card current = this.cards.get(i);
                if (current.getType().equals(CardType.ACE) && current.getValue() == 11) {
                    this.cards.get(i).setValue(1);
                    score -= 10;
                }
            }
        }
        return score;
    }

    public String toString() {
        return this.cards.stream()
            .reduce("", (before, after) -> (before.isEmpty() ? "[" : before + "], [")  + after.getName(), 
            (str1, str2) -> str1 + str2) + "]";
    }
}
