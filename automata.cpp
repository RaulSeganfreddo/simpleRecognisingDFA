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
    // TODO: initialize data structures
    current_state = 0;
    n_states = noStates;
}

/**
 * Reset the automaton to the initial state.
 */
void AbstractDFA::reset() {
    // TODO: reset automaton to initial state
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
    // TODO: do step by going to the next state according to the current
    // state and the read letter.
    bool in_map = false; // variabile booleana utilizzata per assicurarsi che la lettera sia presente nella mappa. In caso contrario vedi sotto

    /* scorro la mappa delle transizioni, per lo stato corrente e la lettera data ci sara' uno stato preciso in cui andare
    * visto che la coppia stato corrente e lettera e' la key della mappa.
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
    // TODO: return if the current state is accepting
    // Scorro il vettore degli stati finali, se lo stato in cui mi trovo e' presente nel vettore allora l'automa accetta la parola data
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
    // TODO: fill in correct number of states

    n_states = word.length() + 2; // vedi esempio sotto

    // riempio il vettore degli stati
    for (int i = 0; i < n_states; i++)
        states.push_back(i);

    /**
    * Per questo DFA, lo stato finale e' uno unico quindi inserisco un solo valore nel vettore degli stati finali.
    * Esempio: (0)-r->(1)-e->(2)-p->(3)-e->(4)-a->(5)-t->(6) (7) == sink state.
    * Quindi visto che la parola repeat ha 6 caratteri, lo stato accettante sara' 6.
    */
    final_states.push_back(word.length());

    // TODO: build DFA recognizing the given word

    string input_word = word;

    /** Eliminazione delle lettere doppie in word:
    * questo perche' nella mappa delle transizioni che creo successivamente non ho bisogno di doppioni,
    * altrimenti si creerebbero transizioni doppie.
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

    /* Creazione mappa delle transizioni per WordDFA
    * Nota: la mappa si crea per qualunque parola, non solo per repeat, basta cambiare la parola richiesta in main.cpp
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
    // TODO: fill in correct number of states
    current_state = 0;
    n_states = 10;

    // TODO: build DFA recognizing comments
    final_states.clear(); // svuoto il vettore degli stati finali utilizzato precedentemente
    final_states.push_back(5); // inserisco lo stato accettante nell'apposito vettore

    for (int i = 0; i < n_states; i++) // riempio il vettore degli stati
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
// TODO: implement accordingly
    /** Questa volta, al posto della map, le transizioni vengono gestite attraverso un switch/case:
    * Questo lo possiamo fare visto che il CommentDFA non cambia a seconda della parola data.
    * Basta quindi solamente gestire i caratteri speciali utilizzati per creare i commenti,
    * ad esempio parentesi e asterischi.
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
