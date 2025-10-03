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

#include <string>
#include <unordered_set>

#include "../util.hh"

#ifndef __DECODER__
#define __DECODER__

using namespace std;

class Decoder
{

  public:
    Decoder()
    {  };

    // this function is the main execution function
    // because it would need to return several things as output,
    // it takes the values to return as references from the caller
    // so that the caller can appropriately manage handle it
    void decode(string instruction, string &operation, int &destination,
                int &source_register1, int &source_register2, int &imm)
    {
        // TODO: your implementation here!
        // an unordered set containing instructions
        unordered_set<string> instructionsList = {"ldi", "add", "sub", "mul", "div", "mod", "end"};

        // Initialize all output parameters
        destination = 0;
        source_register1 = 0;
        source_register2 = 0;
        imm = 0;

        // Extract operation (first 3 characters)
        operation = instruction.substr(0, 3);

        // Check if operation is valid
        if (instructionsList.find(operation) == instructionsList.end()) {
            panic("Invalid instruction");
        }

        // Handle "end" instruction
        if (operation == "end") {
            return;
        }

        // Handle "ldi" instruction (load immediate)
        if (operation == "ldi") {
            // Format: "ldi r5, 1234" -> extract destination and immediate value
            size_t r_pos = instruction.find('r');
            if (r_pos != string::npos) { // if r is found, then we can extract the destination
                size_t comma_pos = instruction.find(',');
                if (comma_pos != string::npos) { // if comma is found,
                    destination = stoi(instruction.substr(r_pos + 1, comma_pos - r_pos - 1)); // extract destination
                    imm = stoi(instruction.substr(comma_pos + 2)); // +2 to skip ", "
                }
            }
        }
        else {
            // Handle other instructions (add, sub, mul, div, mod)
            // Format: "div r3, r2, r1" -> extract destination, source1, source2
            size_t r1_pos = instruction.find('r');
            if (r1_pos != string::npos) { // if r is found, then we can extract the destination
                size_t comma1_pos = instruction.find(',');
                if (comma1_pos != string::npos) {
                    destination = stoi(instruction.substr(r1_pos + 1, comma1_pos - r1_pos - 1));
                    
                    // extract source_register1
                    size_t r2_pos = instruction.find('r', comma1_pos);
                    if (r2_pos != string::npos) {
                        size_t comma2_pos = instruction.find(',', r2_pos);
                        if (comma2_pos != string::npos) {
                            source_register1 = stoi(instruction.substr(r2_pos + 1, comma2_pos - r2_pos - 1));
                            
                            // extract source_register2
                            size_t r3_pos = instruction.find('r', comma2_pos);
                            if (r3_pos != string::npos) {
                                source_register2 = stoi(instruction.substr(r3_pos + 1));
                            }
                        }
                    }
                }
            }
        }
    };
};

#endif // __DECODER__
