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
#include "pipeline_registers/fetch_to_decode.hh"

#ifndef __FETCH_STAGE__
#define __FETCH_STAGE__

class Fetch
{
  private:
    // primary components to perform this stage
    InstructionMemory *inst_mem;
    FetchToDecode *output_register;

    // TODO: your additional fields here!

    int pc = 0;
    bool drain_requested = false;

  public:
    Fetch(InstructionMemory *inst_mem, FetchToDecode *fetch_to_decode_register)
      : inst_mem(inst_mem),
        output_register(fetch_to_decode_register)
        // TODO: construct your additional fields here or in the function!
        
    {  };

    void requestDrain() { drain_requested = true; }

    bool tick()
    {
        // TODO: your implementation here!
        // When draining, stop injecting; drained iff nothing left to hand off.
        if (drain_requested) return !output_register->valid;

        // If downstream hasn’t consumed last fetch, we stall.
        if (output_register->valid) return false;

        // Fetch next line (we rely on END to stop the machine before EOF)
        output_register->valid = true;
        output_register->pc    = pc;
        output_register->inst  = inst_mem->getInstruction(pc); // SAFE: we won't reach EOF because END stops us
        pc += 1;

        return true;
    };
};

#endif // __FETCH_STAGE__
