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

protected:
	std::vector<int> states; // states vector
	std::vector<int> final_states; // final states vector
	int n_states; // variable used to store the total number of states
	int current_state; // variable used to store the number of the current state

	/** Transitions map declaration:
	* the map's key will be a tpair (int, char) where the first int is the current state
	* the char will be the given letter while the second map's value,
	* an int, indicate the next state.
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



