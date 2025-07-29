/**
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Copyright (c) 2025: ST, Pomona College.
 * Contributor: Your Student ID here. Don't deanonymize yourself before grading!
 */

#include <string>

#include "util.hh"

#ifndef __ALU__
#define __ALU__

using namespace std;

class ALU
{
  private:
    // the ALU has three input components, the two sources
    // and the operation that is being used to combine them
    // note: we leave these as class attributes so that the
    // ALU can always produce some output from the inputs,
    // and so the inputs don't change unless done so explicitly
    unsigned int operand1;
    unsigned int operand2;
    string operation;

  public:
    ALU()
      : operand1(0),
        operand2(0),
        operation("add")
    {  };

    void setInputs(string op, unsigned int reg1, unsigned int reg2)
    {
        operand1 = reg1;
        operand2 = reg2;
        operation = op;
    };

    unsigned int execute()
    {
        // main exeuction happens here
        // note: this function does not take inputs, we merely
        // perform an execution on the attributes to emulate charge
        // on the wire
        if (operation == "add") {
            return operand1 + operand2;
        } else if (operation == "sub") {
            return operand1 - operand2;
        } else if (operation == "mul") {
            return operand1 * operand2;
        } else if (operation == "div") {
            return operand1 / operand2;
        } else if (operation == "mod") {
            return operand2 != 0 ? operand1 % operand2 : operand1;
        } else {
            panic("Unknown ALU operation!");
        }

        return 0; // unreachable fall through
    };
};

#endif // __ALU__
