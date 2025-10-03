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

#include "pipeline_registers/decode_to_execute.hh"
#include "pipeline_registers/execute_to_writeback.hh"

#ifndef __HAZARD_CHECKING_UNIT__
#define __HAZARD_CHECKING_UNIT__

class HazardCheckingUnit
{
  private:
    DecodeToExecute *decode_to_execute_register;
    ExecuteToWriteback *execute_to_writeback_register;

  public:
    HazardCheckingUnit(DecodeToExecute *decode_to_execute_register,
                       ExecuteToWriteback *execute_to_writeback_register)
      : decode_to_execute_register(decode_to_execute_register),
        execute_to_writeback_register(execute_to_writeback_register)
    {  };

    bool operandDependence()
    {
        // TODO: your implementation here!
        if(!decode_to_execute_register->valid) return false;
        if(!execute_to_writeback_register->valid) return false;
        if(!execute_to_writeback_register->do_write) return false;

        const int rdP = execute_to_writeback_register->rd;

        if (rdP == 0) return false;   // ignore r0 dependencies

        // If consumer reads rdP as rs1 or rs2, it's a RAW hazard
        return (decode_to_execute_register->rs1 == rdP) || (decode_to_execute_register->rs2 == rdP);
    };
};

#endif // __HAZARD_CHECKING_UNIT__
