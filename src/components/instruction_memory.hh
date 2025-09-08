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
 * Contributor: Your name here!
 */

#include <cassert>
#include <fstream>
#include <string>
#include <vector>

#include "util.hh"

#ifndef __INSTRUCTION_MEMORY__
#define __INSTRUCTION_MEMORY__

using namespace std;

class InstructionMemory
{
  private:
    // main component! we store instructions as strings in a vector
    // to emulate an instruction memory. The fetch interface is using
    // indices to access elements from the vector
    vector<string> instructions;

  public:
    InstructionMemory(string program_filename)
    {
        // the constructor takes an assembly file as input
        // and we assume that every line is one instruction
        // so that we can load it into the instructions vector
        ifstream f(program_filename);
        if (!f) {
            panic("Error opening assembly file!");
        }

        string line;
        while (getline(f, line)) {
            instructions.push_back(line);
        }
    };

    string getInstruction(int idx)
    {
        // accessing instruction memory is as easy as receiving an
        // index (i.e., program counter) and accessing the vector!
        assert(idx >= 0 && (size_t) idx < instructions.size());
        return instructions[idx];
    };
};

#endif // __INSTRUCTION_MEMORY__
