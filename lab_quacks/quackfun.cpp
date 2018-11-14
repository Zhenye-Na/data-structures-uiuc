/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
  if (s.size() == 0) {
    return T();
  } else {
    T tmp = s.top(), result = s.top();
    s.pop();
    result += sum(s);
    s.push(tmp);
    return result;
  }

  // Your code here
  // return T(); // stub return value (0 for primitive types). Change this!
                 // Note: T() is the default value for objects, and 0 for
                 // primitive types

}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of
 * square bracket characters, [, ], and other characters. This function will return
 * true if and only if the square bracket characters in the given
 * string are balanced. For this to be true,
 * all brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is balanced,
 * "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is balanced.
 *
 * You are allowed only the use of one stack in this function, and no other local variables.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
  stack<char> s;

  while (!input.empty())
  {
    char c = input.front();
    input.pop();

    if (c == '[') {
      s.push(c);
    } else {

      if (c != ']') {
        continue;
      }

      if (s.empty()) {
        return false;
      }

      if (c == ']' && s.top() != '[') {
        return false;
      }

      s.pop();
    }
  }

  return s.empty();
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> q2;

    // Your code here
    queue<T> output;

    int counter = 1;
    int length  = 1;

    T temp;
    while (q.size() > 0) {
      temp = q.front();
      q.pop();
      counter--;
      if (length%2 == 0) {
        s.push(temp);
      } else {
        q2.push(temp);
      }
      if (counter == 0 || q.size() == 0) {
        if (length%2 == 0) {
          while (s.size() > 0) {
            output.push(s.top());
            s.pop();
          }
        } else {
          while (q2.size() > 0) {
            output.push(q2.front());
            q2.pop();
          }
        }
        length++;
        counter = length;
      }
    }
    while (output.size() >0) {
      q.push(output.front());
      output.pop();
    }

}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note The back of the queue corresponds to the top of the stack!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    // return false if the size of q and s is not the same
    if (s.size() != q.size()) {
      return false;
    }

    // Your code here
    stack<T> s2;
    queue<T> q2;
    unsigned size = q.size();

    // get the order of q saved in s2
    // save the order of q in q2
    while (!q.empty()) {
      T tmp = q.front();
      q.pop();
      s2.push(tmp);
      q2.push(tmp);
    }

    // get the order of s saved in s3
    stack<T> s3;
    while (!s.empty()) {
      T sTmp = s.top();
      T s2Tmp = s2.top();

      s.pop();
      s2.pop();

      if (sTmp != s2Tmp) {
        return false;
      }

      s3.push(sTmp);
    }

    while (!s3.empty()) {
      T s3Tmp = s3.top();
      s.push(s3Tmp);
      s3.pop();
    }

    while (!q2.empty()) {
      T q2Tmp = q2.front();
      q.push(q2Tmp);
      q2.pop();
    }

    return true;
}

}
