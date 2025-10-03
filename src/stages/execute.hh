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

#include "components/alu.hh"
#include "pipeline_registers/decode_to_execute.hh"
#include "pipeline_registers/execute_to_writeback.hh"

#ifndef __EXECUTE_STAGE__
#define __EXECUTE_STAGE__

class Execute
{
  private:
    // primary components to perform this stage
    ALU *alu;
    DecodeToExecute *input_reg;
    ExecuteToWriteback *output_reg;

    // TODO: your additional fields here!

  public:
    Execute(ALU *alu, DecodeToExecute *decode_to_execute_register,
            ExecuteToWriteback *execute_to_writeback_register)
      : alu(alu),
        input_reg(decode_to_execute_register),
        output_reg(execute_to_writeback_register)
        // TODO: construct your additional fields here or in the function!
    {  };


    bool tick()
    {

	    // TODO: your implementation here!
      // If no incoming work, we're drained iff we also have no pending output
        if (!input_reg->valid) {
            return (!output_reg->valid);
        }

        // If downstream hasn't consumed the previous result, we must stall
        if (output_reg->valid) {
            return false;
        }

        // Produce a new EX->WB entry
        output_reg->valid = true;
        output_reg->pc    = static_cast<unsigned>(input_reg->pc);
        output_reg->rd    = input_reg->rd;

        // Compute result
        const std::string &op = input_reg->operation;

        if (op == "ldi") {
            // Load-immediate bypasses the ALU
            output_reg->result = input_reg->imm;
            output_reg->do_write = true;
        } else if (op == "add" || op == "sub" || op == "mul" ||
                   op == "div" || op == "mod") {
            // Use ALU for binary ops
            // ALU expects unsigned ints; cast operands (semantics remain simple for this lab)
            alu->setInputs(op,
                           static_cast<unsigned>(input_reg->v1),
                           static_cast<unsigned>(input_reg->v2));
            output_reg->result  = static_cast<int>(alu->execute());
            output_reg->do_write = true;
        } else {
            // Unknown op: make this loud in debug; or panic if you prefer
            // panic("Execute: unknown operation: " + op);  // if util.hh allows
            output_reg->result  = 0;
            output_reg->do_write = false;
        }

        // Consume the ID->EX input for this cycle
        input_reg->clear();

        // Not drained this cycle (we just produced work)
        return false;
    };
};

#endif // __EXECUTE_STAGE__
