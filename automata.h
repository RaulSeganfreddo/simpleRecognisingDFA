#pragma once

#include<iostream>
#include<map>
#include<vector>

using namespace std;

typedef std::pair<int, char> tpair;

/**
 * Abstract class for Deterministic Finite Automata.
 */
class AbstractDFA {
	// TODO: use data structure for representing
	// - states
	// - final states (and sink states)
	// - transitions of the form (state, input) -> state
	// - current state

protected:
	std::vector<int> states; // vettore degli stati
	std::vector<int> final_states; // vettore degli stati finali
	int n_states; // variabile usata per tener conto del numero di stati
	int current_state; // variabile usata per tener conto dello stato corrente

	/** Dichiarazione della mappa delle transizioni:
	* la chiave della mappa sara' un tpair (int, char) dove il primo int indica
	* lo stato corrente, il char la lettera data mentre il secondo valore della map,
	* un int, indichera' lo stato successivo basandosi sullo stato corrente e sulla
	* lettera.
	*/
	std::map<tpair, int> mappa;

public:
	/**
	 * Constructor for Abstract DFA.
	 *
	 * @param noStates
	 *            Number of states in the DFA.
	 */
	AbstractDFA(int noStates);

	/**
	 * Reset the automaton to the initial state.
	 */
	void reset();

	/**
	 * Performs one step of the DFA for a given letter. If there is a transition
	 * for the given letter, then the automaton proceeds to the successor state.
	 * Otherwise it goes to the sink state. By construction it will stay in the
	 * sink for every input letter.
	 *
	 * @param letter
	 *            The current input.
	 */
	virtual void doStep(char letter);

	/**
	 * Check if the automaton is currently accepting.
	 *
	 * @return True, if the automaton is currently in the accepting state.
	 */
	bool isAccepting();

	/**
	 * Run the DFA on the input.
	 *
	 * @param inputWord
	 *            stream that contains the input word
	 * @return True, if if the word is accepted by this automaton
	 */
	bool run(const string &inputWord);
};

/**
 * DFA recognizing a given word.
 */
class WordDFA : public AbstractDFA {

public:
	/**
	 * Construct a new DFA that recognizes exactly the given word. Given a word
	 * "foo" the constructed automaton looks like: -> () -f-> () -o-> () -o-> []
	 * from every state (including the final one) every other input letter leads
	 * to a distinguished sink state in which the automaton then remains
	 *
	 * @param word
	 *            A String that the automaton should recognize
	 */
	WordDFA(const string &word);
};

/**
 * DFA recognizing comments.
 */
class CommentDFA : public AbstractDFA {

public:
	/**
	 * Construct a new DFA that recognizes comments within source code. There
	 * are three kinds of comments:
	 *  1. a single line comment that starts with // and ends with a newline
	 *  2. a multiline comment that starts with (* and ends with *)
	 *  3. a multiline comment that starts with { and ends with }
	 */
	CommentDFA();

	/**
	 * Performs one step of the DFA for a given letter. This method works
	 * differently than in the superclass AbstractDFA.
	 *
	 * @param letter
	 *            The current input.
	 */
	virtual void doStep(char letter);
};



