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

#include "components/decoder.hh"
#include "components/register_file.hh"
#include "pipeline_registers/fetch_to_decode.hh"
#include "pipeline_registers/decode_to_execute.hh"

#ifndef __DECODE_STAGE__
#define __DECODE_STAGE__

class Decode
{
  private:
    // primary components to perform this stage
    Decoder *decoder;
    RegisterFile *register_file;
    FetchToDecode *input_reg;
    DecodeToExecute *output_reg;

    // TODO: your additional fields here!

  public:
    Decode(Decoder *decoder, RegisterFile *register_file,
           FetchToDecode *fetch_to_decode_register,
           DecodeToExecute *decode_to_execute_register)
      : decoder(decoder),
        register_file(register_file),
        input_reg(fetch_to_decode_register),
        output_reg(decode_to_execute_register)
        // TODO: construct your additional fields here or in the function!
    {  };

    bool tick()
    {
        // TODO: your implementation here!

        return false;
    };
};

#endif // __DECODE_STAGE__
