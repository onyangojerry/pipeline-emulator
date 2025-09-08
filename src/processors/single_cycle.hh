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

#include "components/instruction_memory.hh"
#include "components/decoder.hh"
#include "components/register_file.hh"
#include "components/alu.hh"

#include <string>

#ifndef __SINGLE_CYCLE__
#define __SINGLE_CYCLE__

class SingleCycleProcessor
{
  private:
    // declare our components
    InstructionMemory instruction_memory;
    Decoder decoder;
    RegisterFile register_file;
    ALU alu;

    // TODO: your additional fields here!

    // some stats for neat accounting
    int cycles_executed;

  public:
    SingleCycleProcessor(string program_filename)
      : instruction_memory(program_filename),
        decoder(),
        register_file(8),
        alu(),
        // TODO: any additional fields constructed here or in the function!
        cycles_executed(0)
    {  };

    void dumpRegisters()
    {
        for (int i = 0; i < 8 /* num_registers */; i++) {
            cout << "r" << i << ":    " << register_file.getRegister(i);
            if (i % 2 == 0) {
                cout << "\t";
            } else {
                cout << "\n";
            }
        }
    };

    void executeProgram()
    {
         /* Main Execution Loop */
         while (true) {
            cycles_executed++;

            // TODO: your implementation here!
        }

        // dump stats and registers!
        cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
        cout << " ~~~~~~ Final stats (single cycle) ~~~~~ " << endl;
        cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;

        cout << "cycles run     :   " << cycles_executed << endl;

        cout << "\n\n ~~~ Register Dump ~~~ " << endl;
        dumpRegisters();
    };
};

#endif // __SINGLE_CYCLE__
