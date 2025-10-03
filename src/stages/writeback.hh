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

#include "components/register_file.hh"
#include "pipeline_registers/execute_to_writeback.hh"

#ifndef __WRITEBACK_STAGE__
#define __WRITEBACK_STAGE__

class Writeback
{
  private:
    // primary components to perform this stage
    RegisterFile *register_file;
    ExecuteToWriteback *input_reg;

    // TODO: your additional fields here!

  public:
    Writeback(RegisterFile *register_file,
              ExecuteToWriteback *execute_to_writeback_register)
      : register_file(register_file),
        input_reg(execute_to_writeback_register)
        // TODO: construct your additional fields here or in the function!
    {  };

    // Return true when this stage is drained (no work present this cycle).
    bool tick()
    {
        // TODO: your implementation here!
        // If there's nothing to commit, WB is empty/drained this cycle.
        if (!input_reg->valid) {
            return true;
        }

        // Commit result to the architectural state if requested.
        if (input_reg->do_write /* commit control */ && input_reg->rd != 0 /* optional r0 guard */) {
            register_file->setRegister(input_reg->rd, input_reg->result);
        }

        // Consume the EX->WB bubble for this cycle.
        input_reg->clear();

        // We just did work this cycle; not drained until next cycle when input is empty.
        return false;
    };
};

#endif // __WRITEBACK_STAGE__
