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

#include <vector>
#include <cassert>

#ifndef __REGISTER_FILE__
#define __REGISTER_FILE__

using namespace std;

class RegisterFile
{
  private:
    // the registers are the main feature of the component!
    // to ensure that we can support variable numbers of registers
    // they are initially declared as an empty vector
    vector<unsigned int> registers;
    const int num_registers;

  public:
    RegisterFile(int num_registers)
      : num_registers(num_registers)
    {
        for (int i = 0; i < num_registers; i++) { registers.push_back(0); }
    };

    unsigned int getRegister(int idx)
    {
        assert(idx < num_registers);
        return registers[idx];
    };

    void setRegister(int idx, unsigned int data_in)
    {
        assert(idx < num_registers);
        if (idx > 0) {
            registers[idx] = data_in;
        }
    };
};

#endif // __REGISTER_FILE__
