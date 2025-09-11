import sys
import time

regs = [0 for _ in range(8)]
print(f"let's produce the step by step output for {sys.argv[1]}")

f = open(sys.argv[1])
instructions = [line.strip() for line in f.readlines()]
f.close()

for inst_num, inst in zip(range(len(instructions)), instructions):
	if inst_num >= 25:
		break

	tokens = [x.replace('r', '') if ',' not in x else x[:-1].replace('r', '') for x in inst.split()]
	try:
		if tokens[0] == 'ldi':
			regs[int(tokens[1])] = int(tokens[2])
		elif tokens[0] == 'add':
			regs[int(tokens[1])] = int(regs[int(tokens[2])]) + int(regs[int(tokens[3])])
		elif tokens[0] == 'sub':
			regs[int(tokens[1])] = int(regs[int(tokens[2])]) - int(regs[int(tokens[3])])
		elif tokens[0] == 'mul':
			regs[int(tokens[1])] = int(regs[int(tokens[2])]) * int(regs[int(tokens[3])])
		elif tokens[0] == 'div':
			regs[int(tokens[1])] = int(regs[int(tokens[2])]) // int(regs[int(tokens[3])])
		elif tokens[0] == 'mod':
			regs[int(tokens[1])] = int(regs[int(tokens[2])]) % int(regs[int(tokens[3])])
		elif tokens[0] != 'end':
			exit('Unrecognized instruction!')
	except IndexError:
		exit('Illegal instruction format!')

	reg_str = "\t".join(["r" + str(i) + " :   " + str(regs[i]) for i in range(len(regs))])
	print(f'instruction {inst_num} :  {reg_str}')

if tokens[0] != 'end':
	exit('Did not reach end of program!')

print(f'Instructions Executed:   {len(instructions)}')
