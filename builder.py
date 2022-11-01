import code_parser
import os
import sys

options = {
	'number_of_columns': 2,
	'characters_in_a_row': 87,
	'expandtab': 2,
	'width': 297,
	'height': 210,
	'margin_top': 5,
	'margin_bottom': 6,
	'margin_left': 7,
	'margin_middle': 4,
	'margin_right': 7,

	'big_letter_box_percent': 0.8,
	'big_letter_size_percent': 0.7,
	'big_letter_colors': {
		'C': (0.2, 0.2, 0.2),
		# 'B': (0.7, 0, 0),
		'DS': (0.7, 0, 0),
		'F&M': (0.7, 0.3, 0),
		'Ge': (0.7, 0.7, 0),
		'Gr': (0, 0.7, 0),
		'M': (0, 0.7, 0.3),
		'Mi': (0, 0.7, 0.7),
		'NT': (0, 0, 0.7),
		'S': (0.3, 0, 0.7),
		# 'T': (0.6, 0.6, 0.6),
	},
	'big_letter_font': {
		'is_bold': True,
		'color': (1, 1, 1),
	},

	'header_decorations': {
		'is_bold': True,
		'color': (0, 0, 0),
		'bg_color': (0, 1, 0, 0.5),
		'border_color': (0, 0, 0),
	},

	'right_wrap_decorations': {
		'is_bold': True,
		'color': (1, 1, 1),
		'bg_color': (1, 0, 0),
	},

	'left_wrap_decorations': {
		'is_bold': True,
		'color': (1, 1, 1),
		'bg_color': (0, 0, 1),
	},

	'page_number_decorations': {
		'is_italic': True,
		'color': (0, 0, 0),
	},

	'date_decorations': {
		'is_italic': True,
		'color': (0, 0, 0),
	},

	'page_summary_decorations': {
		'is_italic': True,
		'color': (0, 0, 0),
	},

	'latex_options': {
		'input_tex': "???",
		'width': "???",
		'zoom': 2.5,
		'border': (5,   # Left.
							 5,   # Bottom.
							 5,   # Right.
							 5),  # Top.
	},
}

def CheckFileType(filename):
	if filename.endswith('.cpp'):
		return (filename, 'C++', 'default')
	elif filename.endswith('.tex'):
		return (filename, 'LaTeX', 'default')
	else:
		return (filename, 'text', 'default')

def FindAllSourceCode(code_dir):
	sources = []
	for (dirpath, dirnames, filenames) in os.walk(code_dir):
		for filename in filenames:
			path = os.path.join(dirpath, filename)
			file_type = CheckFileType(path)
			if file_type:
				sources.append(file_type)
	return sources

if len(sys.argv) != 3:
	print("Usage: {} code_dir/ output.pdf".format(sys.argv[0]))
	sys.exit(1)

options['code_dir'] = sys.argv[1]
options['output_pdf'] = sys.argv[2]

cp = code_parser.CodeParser(options)

files = []

try:
	with open('FILES', 'r') as f:
		all_sources = [CheckFileType(x) for x in f.read().split('\n') if x.strip() and x.strip()[0] != '#']
		from_file = True
except FileNotFoundError:
	all_sources = FindAllSourceCode(options['code_dir'])
	from_file = False


for filename, lang, style in all_sources:
	files.append({"filename": filename,
	              "lang":     lang,
	              "style":    style})

def key_to_compare(f):
	global options
	filename = os.path.relpath(f["filename"], options["code_dir"])
	directory = os.path.dirname(filename)
	basename = os.path.basename(filename)
	if directory == "":
		dir_weight = 0
		if basename == "geany-config":
			basename = "1"
		if basename == "makra.cpp":
			basename = "2"
		elif basename == "Rzeczy_Na_Dzien_Probny.cpp":
			basename = "3"
		else:
			print(f'{f = }', file=sys.stderr);
			# assert False
	return (directory, basename.lower())

if not from_file:
	files.sort(key=key_to_compare)

for f in files:
	new_options = dict(options)
	new_options['lang'] = f['lang']
	new_options['style'] = f['style']
	cp.AddCodeFile(f['filename'], new_options)

cp.GeneratePdf(options)
