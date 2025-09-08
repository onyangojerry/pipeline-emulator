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

  public:
    Fetch(InstructionMemory *inst_mem, FetchToDecode *fetch_to_decode_register)
      : inst_mem(inst_mem),
        output_register(fetch_to_decode_register)
        // TODO: construct your additional fields here or in the function!
    {  };

    bool tick()
    {
        // TODO: your implementation here!

        return false;
    };
};

#endif // __FETCH_STAGE__
