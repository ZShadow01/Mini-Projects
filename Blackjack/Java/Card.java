public class Card {
    private final CardType type;
    private int value;
    private final String name;

    public Card(CardType cardType) {
        /*
         * Initialize card object -> value of ACE card can change
         */
        this.type = cardType;
        this.name = this.type.name();
        
        switch(cardType) {
            case C2:
            case C3:
            case C4:
            case C5:
            case C6:
            case C7:
            case C8:
            case C9:
                this.value = cardType.ordinal() + 1;
                break;
            case C10:
            case JACK:
            case QUEEN:
            case KING:
                this.value = 10;
                break;
            case ACE:
                this.value = 11;
                break;
        }
    }

    public void setValue(int value) {
        this.value = value;
    }

    public int getValue() {
        return this.value;
    }

    public CardType getType() {
        return this.type;
    }

    public String getName() {
        return this.name;
    }
}
