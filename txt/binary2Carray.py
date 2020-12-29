"""
This is a simple script to convert the stale binary
to an easy to copy and paste C++ array
"""

txt_directory = "TinyTetrisTitleScreen_binary.txt"
txt_output_directory = "TinyTetrisTitleScreen_binary_Carray.txt"

"""
Loads the text file and returns the binary as text
"""
def loadFile(file_dir: str):
	with open(file_dir, 'r') as file:
		return file.read()

def convert2Carray(binary_text):
	binary_text = binary_text.splitlines()
	bytary_text = "{\n"# The name is funny, Lolz
	at_what_line = 1
	for binary_line in binary_text:
		n=8# every 8 bits
		binary = [binary_line[i:i+n] for i in range(0, len(binary_line), n)]# separate into 8*2 bytes
		binary = ['0B'+binary[i] for i in range(0, len(binary))]# add '0B' at the start
		binary = "\t" + ", ".join(binary)# rejoin the elements
		if at_what_line != len(binary_text):# put commas at the end of each line except for the last line
			binary += ","
		binary += "\n"
		bytary_text += binary

		at_what_line += 1

	bytary_text += "}"

	return bytary_text

def saveFile(file_dir: str, data: str):
	with open(file_dir, 'w') as file:
		file.write(data)

saveFile(
	txt_output_directory,
	convert2Carray(
		loadFile(txt_directory)
	)
)

