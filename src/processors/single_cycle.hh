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

#include "../components/instruction_memory.hh"
#include "../components/decoder.hh"
#include "../components/register_file.hh"
#include "../components/alu.hh"

#include <string>
#include <iostream>

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
    int program_counter;
    // some stats for neat accounting
    int cycles_executed;

  public:
    SingleCycleProcessor(std::string program_filename)
      : instruction_memory(program_filename),
        decoder(),
        register_file(8),
        alu(),
        // TODO: any additional fields constructed here or in the function!
        program_counter(0),
        cycles_executed(0)
        
    {  };

    void dumpRegisters()
    {
        for (int i = 0; i < 8 /* num_registers */; i++) {
            std::cout << "r" << i << ":    " << register_file.getRegister(i);
            if (i % 2 == 0) {
                std::cout << "\t";
            } else {
                std::cout << "\n";
            }
        }
    };

    void executeProgram()
    {

      /* Main Execution Loop */
      while (true) {
        cycles_executed++;

        // TODO: your implementation here!
        
        // dedited file path to make assembly files accessible

        // fetch instruction
        std::string instruction = instruction_memory.getInstruction(program_counter);
        // decode the instruction
        std::string operation;
        int destination;
        int source_register1;
        int source_register2;
        int imm;
        decoder.decode(instruction, operation, destination, source_register1, source_register2, imm);

        // handle end instruction
        if (operation == "end" || operation == "END") {
            break;
        }

        // execute the instruction
        if (operation == "ldi") {
          if (destination != 0) {
            register_file.setRegister(destination, static_cast<unsigned int>(imm));

          }
            
        } else {
            unsigned int oper1 = register_file.getRegister(source_register1);
            unsigned int oper2 = register_file.getRegister(source_register2);
            alu.setInputs(operation, oper1, oper2);
            unsigned int result = alu.execute();
            if (destination != 0) {
                    register_file.setRegister(destination, result);
                }
            //register_file.setRegister(destination, result);
        }

        // update program counter
        program_counter++;

      }

        // dump stats and registers!
        std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
        std::cout << " ~~~~~~ Final stats (single cycle) ~~~~~ " << std::endl;
        std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;

        cout << "cycles run     :   " << cycles_executed << endl;

        cout << "\n\n ~~~ Register Dump ~~~ " << endl;
        dumpRegisters();
    };
};

#endif // __SINGLE_CYCLE__

