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
 * Contributor: Jerry Onyango
 */

#include "components/instruction_memory.hh"
#include "components/decoder.hh"
#include "components/register_file.hh"
#include "components/alu.hh"
#include "components/forwarding_unit.hh"
#include "pipeline_registers/fetch_to_decode.hh"
#include "pipeline_registers/decode_to_execute.hh"
#include "pipeline_registers/execute_to_writeback.hh"
#include "stages/fetch.hh"
#include "stages/decode.hh"
#include "stages/execute.hh"
#include "stages/writeback.hh"

#include <string>

#ifndef __FORWARDING__
#define __FORWARDING__

class ForwardingProcessor
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
    ForwardingUnit forwarding_unit;

    // TODO: your additional fields here!

    // some stats for neat accounting
    int cycles_executed;

  public:
    ForwardingProcessor(string program_filename)
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
        forwarding_unit(&decode_to_execute_register,
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
    bool done = false;
    do {
        cycles_executed++;

        // 1) Snapshot fetch->decode for possible restore on stall
        FetchToDecode f2d_snapshot = fetch_to_decode_register;

        // 2) Snapshot execution input before execution tick (detect the one un-forwardable case)
        DecodeToExecute ex_in_snapshot = decode_to_execute_register;

        // advance pipeline stages for the next step
        [[maybe_unused]] bool writeback_drained = writeback_stage.tick();
        [[maybe_unused]] bool execute_drained = execute_stage.tick();
        [[maybe_unused]] bool decode_drained = decode_stage.tick();

        // TODO: check for hazard
        // Forward execution->writeback → decode->execution (patch v1/v2 in place)
        (void)forwarding_unit.operandDependence();

        // Remaining hazard: consumer depends on instruction that fed execution this cycle
        auto writes_dest = [&](const DecodeToExecute& in)->bool {
            if (!in.valid) return false;
            if (in.rd == 0) return false;
            const std::string& op = in.operation;
            return (op=="ldi" || op=="add" || op=="sub" || op=="mul" || op=="div" || op=="mod");
        };

        bool cant_forward = false;
        if (decode_to_execute_register.valid && writes_dest(ex_in_snapshot)) {
            int rd_prev = ex_in_snapshot.rd;
            cant_forward = (decode_to_execute_register.rs1 == rd_prev) ||
                           (decode_to_execute_register.rs2 == rd_prev);
        }

        if (cant_forward) {
            decode_to_execute_register.clear();

            if (!fetch_to_decode_register.valid && f2d_snapshot.valid) {
                fetch_to_decode_register = f2d_snapshot;
            }

            done = false;
            continue;  // next cycle, producer moves to execute->writeback; then forwarding works
        }

        // start exit sequence
        if (decode_drained) {
            fetch_stage.requestDrain();
        }
        bool fetch_drained = fetch_stage.tick();

        // Finish only when all stages drained
        done = fetch_drained && decode_drained && execute_drained && writeback_drained;

    } while (!done);

    // ... stats + dump ...



        cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
        cout << " ~~~~~ Final stats (forwarding) ~~~~~ " << endl;
        cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;

        cout << "cycles run     :   " << cycles_executed << endl;

        cout << "\n\n ~~~ Register Dump ~~~ " << endl;
        dumpRegisters();
    };
};

#endif // __HAZARD_CHECKING__
