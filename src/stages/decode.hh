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

#include <iostream>
#include <string>
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
    // draining state: set after we consume END once
    bool end_seen = false;

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
        // No new input this cycle
        if (!input_reg->valid) {
            // Drained only after END has been seen and we have no pending output
            bool drained = (end_seen && !output_reg->valid);


            // std::cout << "DEBUG: Decode no input - end_seen=" << end_seen 
            //           << " !output_reg->valid=" << !output_reg->valid 
            //           << " drained=" << drained << std::endl;


            return drained;
        }

        // Downstream (EX) still holds last cycle's decode → stall
        if (output_reg->valid) {
            return false;
        }

        // Decode the incoming instruction line
        std::string op;
        int rd=0, rs1=0, rs2=0, imm=0;
        decoder->decode(input_reg->inst, op, rd, rs1, rs2, imm);

        // If this is the terminating instruction, start the drain sequence:
        if (op == "end" || op == "END") {

            //std::cout << "DEBUG: END instruction seen, setting end_seen = true" << std::endl;

            end_seen = true;
            // consume the input, emit NO work (bubble)
            input_reg->clear();

            // drained when END has been seen and both sides are empty
            bool drained = (end_seen && !output_reg->valid && !input_reg->valid);

            
            // std::cout << "DEBUG: Decode drain check after END: end_seen=" << end_seen 
            //           << " !output_reg->valid=" << !output_reg->valid 
            //           << " !input_reg->valid=" << !input_reg->valid 
            //           << " drained=" << drained << std::endl;


            return drained;
        }

        // Normal path: populate ID->EX register for Execute
        output_reg->valid     = true;
        output_reg->pc        = input_reg->pc;
        output_reg->operation = op;
        output_reg->rd        = rd;
        output_reg->rs1       = rs1;
        output_reg->rs2       = rs2;
        output_reg->imm       = imm;

        // Read operands now (simple 4-stage; no forwarding here)
        // For "ldi", rs1/rs2 may be 0/unused; that's fine.
        output_reg->v1 = register_file->getRegister(rs1);
        output_reg->v2 = register_file->getRegister(rs2);

        // Consume the IF->ID register
        input_reg->clear();

        // Even if END was seen previously, we aren't drained while emitting work.
        return (end_seen && !output_reg->valid && !input_reg->valid);
        
    };
};

#endif // __DECODE_STAGE__
