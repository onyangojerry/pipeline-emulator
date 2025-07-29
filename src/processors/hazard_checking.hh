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

#include "components/instruction_memory.hh"
#include "components/decoder.hh"
#include "components/register_file.hh"
#include "components/alu.hh"
#include "components/hazard_checking_unit.hh"
#include "pipeline_registers/fetch_to_decode.hh"
#include "pipeline_registers/decode_to_execute.hh"
#include "pipeline_registers/execute_to_writeback.hh"
#include "stages/fetch.hh"
#include "stages/decode.hh"
#include "stages/execute.hh"
#include "stages/writeback.hh"

#include <string>

#ifndef __HAZARD_CHECKING__
#define __HAZARD_CHECKING__

class HazardCheckingProcessor
{
  private:
    // declare our components
    InstructionMemory instruction_memory;
    Decoder decoder;
    RegisterFile register_file;
    ALU alu;

    // declare inter-stage registers
    FetchToDecode fetch_to_decode_register;
    DecodeToExecute decode_to_execute_register;
    ExecuteToWriteback execute_to_writeback_register;

    // declare our stages
    Fetch fetch_stage;
    Decode decode_stage;
    Execute execute_stage;
    Writeback writeback_stage;

    // to maintain state about whether we are in a hazard or not!
    HazardCheckingUnit hazard_checking_unit;

    // TODO: your additional fields here!

    // some stats for neat accounting
    int cycles_executed;

  public:
    HazardCheckingProcessor(string program_filename)
      : instruction_memory(program_filename),
        decoder(),
        register_file(8 /* num_registers */),
        alu(),
        fetch_to_decode_register(),
        decode_to_execute_register(),
        execute_to_writeback_register(),
        fetch_stage(&instruction_memory, &fetch_to_decode_register),
        decode_stage(&decoder, &register_file, &fetch_to_decode_register,
                     &decode_to_execute_register),
        execute_stage(&alu, &decode_to_execute_register,
                      &execute_to_writeback_register),
        writeback_stage(&register_file, &execute_to_writeback_register),
        hazard_checking_unit(&decode_to_execute_register,
                            &execute_to_writeback_register),
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
        bool done = false;
        do {
            cycles_executed++;

            // advance pipeline stages for the next step
            [[maybe_unused]] bool writeback_drained = writeback_stage.tick();
            [[maybe_unused]] bool execute_drained = execute_stage.tick();
            [[maybe_unused]] bool decode_drained = decode_stage.tick();

            // TODO: check for hazard
            if (false) {
            } else {
                // start exit sequence
                if (decode_drained) {
                    // TODO: use your exit methodology from the previous section here!
                }
                [[maybe_unused]] bool fetch_drained = fetch_stage.tick();
            }

            done = writeback_drained;
        } while (!done);

        // dump stats and registers!
        cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
        cout << " ~~~~~ Final stats (hazard checking) ~~~~~ " << endl;
        cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;

        cout << "cycles run     :   " << cycles_executed << endl;

        cout << "\n\n ~~~ Register Dump ~~~ " << endl;
        dumpRegisters();
    };
};

#endif // __HAZARD_CHECKING__
