import random


# Constants
WINNING_SCORE = 21
DECKS = 8  # Standard amount of decks used in Blackjack
CARDS = ['ACE', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'JACK', 'QUEEN', 'KING']


def get_hand_value(hand: list):
    """
    Calculate the card values.
    KINGs, QUEENs and JACKs are worth 10,
    ACE is worth 1 or 11 (player can choose),
    the rest are worth as much as their own number
    """
    hand = sorted(hand, key=lambda k: k == 'ACE')
    values = []

    for card in hand:
        if card == 'KING' or card == 'QUEEN' or card == 'JACK':
            values.append(10)
        elif card == 'ACE':
            # ACE's default value is 11, change ACE value to 1 if the current value is over 21
            values.append(11)
            for i in range(len(values)):
                if hand[i] == 'ACE' and values[i] == 11 and sum(values) > WINNING_SCORE:
                    values[i] = 1
        else:
            values.append(int(card))

    return sum(values)


def str_hand(hand: list) -> str:
    """
    Format the list of cards to a string
    Example:
        ['ACE', '1', ..., 'QUEEN', 'KING'] -> "[ACE], [1], ..., [QUEEN], [KING]"
    """
    return "[" + "], [".join(hand) + "]"


def run_player(current_stack: list, player_hand: list) -> int:
    """
    The player can hit to draw cards or stand to end the turn (no double downs, splits, etc.)
    Unlike the dealer, the player has no limitations and can choose to hit whenever (unless the player is already busted)
    """
    score = get_hand_value(player_hand)
    while score < WINNING_SCORE:
        print("Player's turn")
        print("Cards:", str_hand(player_hand))
        print("Current score:", score)

        user_input = input('HIT or STAND: ').upper()
        if user_input == 'HIT':
            player_hand.append(current_stack.pop(0))
            score = get_hand_value(player_hand)
        elif user_input == 'STAND':
            print()
            return score
        print()
    return score


def run_dealer(current_stack: list, dealer_hand: list) -> int:
    """
    The dealer has to draw cards if the dealer's score is less than 17.
    Once the score is equal to 17 or above, the dealer is required to stand.
    """
    score = get_hand_value(dealer_hand)
    while score < 17:
        dealer_hand.append(current_stack.pop(0))
        score = get_hand_value(dealer_hand)
    return score


def main():
    # Create card stack and shuffle
    current_stack = []
    for i in range(DECKS * len(CARDS) * 4):  # Times 4 because a deck of cards has 4 different symbols
        current_stack.append(CARDS[i % len(CARDS)])
    random.shuffle(current_stack)

    # Always take cards from the top of the stack
    current_player_hand = [current_stack.pop(0), current_stack.pop(0)]
    current_dealer_hand = [current_stack.pop(0), current_stack.pop(0)]

    # Start the game
    player_score = run_player(current_stack, current_player_hand)
    print("Player:", str_hand(current_player_hand), "-> " + str(player_score))

    dealer_score = run_dealer(current_stack, current_dealer_hand)
    print("Dealer:", str_hand(current_dealer_hand), "-> " + str(dealer_score))

    # Dealing the scores
    if player_score > WINNING_SCORE:
        print("BUSTED")
        return
    
    if dealer_score > WINNING_SCORE:
        print("Dealer BUSTED")
        return

    # Check which score is closer to 21
    p_dist, d_dist = abs(WINNING_SCORE - player_score), abs(WINNING_SCORE - dealer_score)
    if p_dist < d_dist:
        print("You WIN")
    elif p_dist > d_dist:
        print("You LOSE")
    else:
        print("DRAW")


if __name__ == '__main__':
    main()
