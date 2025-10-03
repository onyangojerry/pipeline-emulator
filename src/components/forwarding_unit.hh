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

#include "pipeline_registers/decode_to_execute.hh"
#include "pipeline_registers/execute_to_writeback.hh"

#ifndef __FORWARDING_UNIT__
#define __FORWARDING_UNIT__

class ForwardingUnit
{
  private:
    DecodeToExecute *decode_to_execute_register;
    ExecuteToWriteback *execute_to_writeback_register;

    static inline bool writes_dest(const std::string& op) {
        return (op=="ldi" || op=="add" || op=="sub" || op=="mul" || op=="div" || op=="mod");
    }

  public:
    ForwardingUnit(DecodeToExecute *decode_to_execute_register,
                   ExecuteToWriteback *execute_to_writeback_register)
      : decode_to_execute_register(decode_to_execute_register),
        execute_to_writeback_register(execute_to_writeback_register)
    {  };

    bool operandDependence()
    {
        // TODO: your implementation here!
        if (!decode_to_execute_register->valid) return false;     // nothing to consume
        // If EX->WB holds a producer, forward its result into ID->EX.v1/v2
        if (execute_to_writeback_register->valid && execute_to_writeback_register->do_write && execute_to_writeback_register->rd != 0) {
            if (decode_to_execute_register->rs1 == execute_to_writeback_register->rd) decode_to_execute_register->v1 = execute_to_writeback_register->result;
            if (decode_to_execute_register->rs2 == execute_to_writeback_register->rd) decode_to_execute_register->v2 = execute_to_writeback_register->result;
        }
        return false;
    };
};

#endif // __FORWARDING_UNIT__
