#include <iostream>
#include "automata.h"

using namespace std;

/**
 * Constructor for Abstract DFA.
 *
 * @param noStates
 *            Number of states in the DFA.
 */
AbstractDFA::AbstractDFA(int noStates) {
    current_state = 0;
    n_states = noStates;
}

/**
 * Reset the automaton to the initial state.
 */
void AbstractDFA::reset() {
    current_state = 0;
}

/**
 * Performs one step of the DFA for a given letter. If there is a transition
 * for the given letter, then the automaton proceeds to the successor state.
 * Otherwise it goes to the sink state. By construction it will stay in the
 * sink for every input letter.
 *
 * @param letter
 *            The current input.
 */
void AbstractDFA::doStep(char letter) {
    bool in_map = false; // variabile booleana utilizzata per assicurarsi che la lettera sia presente nella mappa. In caso contrario vedi sotto

    /* Looking through transitions map, for the current state and the given letter there will be a precise state where to go.
    * considering that the pair current state and letter is the map's key.
    */
    for (auto m : mappa)
    {
        if (m.first.first == current_state && m.first.second == letter)
        {
            current_state = m.second;
            in_map = true;
            break;
        }
    }
    // Se la lettera data non e' presente nella mappa, l'automa va nel sink state
    if (!in_map)
        current_state = n_states - 1;
}

/**
 * Check if the automaton is currently accepting.
 *
 * @return True, if the automaton is currently in the accepting state.
 */
bool AbstractDFA::isAccepting() {
    // Scan final states vector, if my current state is in that vector, return true, else we return false
    for (int s : final_states)
    {
        if (s == current_state)
            return true;
    }
    return false;
}

/**
 * Run the DFA on the input.
 *
 * @param inputWord
 *            stream that contains the input word
 * @return True, if if the word is accepted by this automaton
 */
bool AbstractDFA::run(const string &inputWord) {
    this->reset();
    for (int i = 0; i < inputWord.length(); i++) {
        doStep(inputWord[i]);
    }
    return isAccepting();
}


/**
 * Construct a new DFA that recognizes exactly the given word. Given a word
 * "foo" the constructed automaton looks like: -> () -f-> () -o-> () -o-> []
 * from every state (including the final one) every other input letter leads
 * to a distinguished sink state in which the automaton then remains
 *
 * @param word
 *            A String that the automaton should recognize
 */
WordDFA::WordDFA(const string &word) : AbstractDFA(0) {

    n_states = word.length() + 2; // vedi esempio sotto

    // riempio il vettore degli stati
    for (int i = 0; i < n_states; i++)
        states.push_back(i);

    /**
    * For this DFA, the final state is only one, quindi so I insert only one value in the final states vector.
    * Example: (0)-r->(1)-e->(2)-p->(3)-e->(4)-a->(5)-t->(6) (7) == sink state.
    * Considering that the word "repeat" has 6 characters, the final state will be 6.
    */
    final_states.push_back(word.length());

    string input_word = word;

    /** Elimination of duplicate letters in the word:
    * this because the transitions map created do not need duplicates
    * otherwise will be created duplicate transitions.
    */
    for (int i = 0; i < input_word.length(); i++)
    {
        for (int j = i + 1; j < input_word.length(); j++)
        {
            if (input_word[i] == input_word[j])
            {
                input_word.erase(input_word.begin() + j);
            }
        }
    }

    /* Transitions map creations for WordDFA.
    * Note: map is created for any word, not only for "repeat", you just need to changhe the word in main.cpp
    */
    string original = word;

    for (int i = 0; i < n_states; i++)
    {
        for (int j = 0; j < input_word.length(); j++)
        {
            if (input_word[j] == original[i])
                mappa[ {i, input_word[j]}] = i + 1;
            else
                mappa[ {i, input_word[j]}] = word.length() + 1;
        }
    }
}

/**
 * Construct a new DFA that recognizes comments within source code. There
 * are three kinds of comments: single line comment that starts with // and ends
 * with a newline, multiline comments that starts with (* and ends with *), and
 * multiline comments that starts with { and ends with }
 */
CommentDFA::CommentDFA() : AbstractDFA(0) {
    current_state = 0;
    n_states = 10;
    final_states.clear(); // empting final_states vector used previously
    final_states.push_back(5); // insert of the final state in the final_states vector

    for (int i = 0; i < n_states; i++) // filling states vector
        states.push_back(i);
}

/**
 * Performs one step of the DFA for a given letter. This method works
 * differently than in the superclass AbstractDFA.
 *
 * @param letter
 *            The current input.
 */
void CommentDFA::doStep(char letter) {
    /** This time, instead of with the map, transitions are managed through a simple switch/case:
    * We can do this because CommentDFA do not change in size depending on the given word.
    * We just need to manage special characters used to create comments,
    * like brackets and asterisks.
    */
    switch (current_state)
    {
    case 0:
    {
        if (letter == '(')
        {
            current_state = 1;
            break;
        }
        if (letter == '{')
        {
            current_state = 6;
            break;
        }
        if (letter == '/')
        {
            current_state = 7;
            break;
        }
    }
    case 1:
    {
        if (letter == '*')
        {
            current_state = 2;
            break;
        }
    }
    case 2:
    {
        if (letter != '*')
        {
            current_state = 3;
            break;
        }
        if (letter == '*')
        {
            current_state = 2;
            break;
        }
    }
    case 3:
    {
        if (letter != '*')
        {
            current_state = 3;
            break;
        }
        if (letter == '*')
        {
            current_state = 4;
            break;
        }
    }
    case 4:
    {
        if (letter == '*')
        {
            current_state = 4;
            break;
        }
        if (letter == ')')
        {
            current_state = 5;
            break;
        }
        if (letter != '*' && letter != ')')
        {
            current_state = 3;
            break;
        }
    }
    case 5:
    {
        current_state = 9;
        break;
    }
    case 6:
    {
        if (letter != '}')
        {
            current_state = 6;
            break;
        }
        if (letter == '}')
        {
            current_state = 5;
            break;
        }
    }
    case 7:
    {
        if (letter == '/')
        {
            current_state = 8;
            break;
        }
    }
    case 8:
    {
        if (letter != '\n')
        {
            current_state = 8;
            break;
        }
        if (letter == '\n')
        {
            current_state = 5;
            break;
        }
    }
    case 9:
    {
        current_state = 9;
        break;
    }
    default:
    {
        current_state = 9;
        break;
    }
    }
}
