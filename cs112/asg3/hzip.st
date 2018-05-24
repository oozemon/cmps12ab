#!/afs/cats.ucsc.edu/courses/cmps112-wm/usr/smalltalk/bin/gst -f

"
Usman Zahid 
uzahid@ucsc.edu

For the CMPS 112 course Fall 2017 at UC Santa Cruz

USAGE: 

-d debug info is printed

-t the compression algo is ran, and the decoding tree is printed to
stdout.

-c input file is compressed and written to output file, if 
specified or std out if not

-u input file is assumed to be compressed, 
is uncompressed and written to output file stdout
$hzip.st -dctu inputfile [outfile]
"


execname := '$RCSfile: hzip.st,v $' =~ '.*: (.*),v.*' at: 1.
nl := Character nl.


FileStream extend [
   |bitno bitplace|
   clearByte [
      bitno := 8.
      bitplace := 0.
   ]
   flushByte [
   |char|
      bitno = 8 ifFalse: [
      char := Character value: bitplace asInteger.
      self nextPut: char.
      self clearByte.
      ]
   ]
   writeBit: bit [
      bitplace isNil ifTrue: [self clearByte].
      bitno = 0 ifTrue: [self flushByte].
      bitplace := bitplace bitAt: bitno put: bit.
      bitno := bitno - 1.
   ]
   clearBits [
      bitno := 0.
   ]
   fillByte [
       bitplace := self next.
      bitno := 8.
   ] 
   nextBit [
      |bit|
      bitno isNil ifTrue: [self clearBits].
      bitno = 0 ifTrue: [self fillByte].
      bitplace isNil ifTrue: [ ^ nil ].
      bit := bitplace value bitAt: bitno.
      bitno := bitno - 1.
      ^ bit.
   ]
   bitChar: char [
      |bit charval bitindex|
      charval := char value.
      bitindex := 8. 
      [bitindex ~= 0] whileTrue: [
      bit := charval bitAt: bitindex.
      bitindex := bitindex - 1. 
      self writeBit: bit.
      ].
      (charval = 0) | (charval = 256) ifTrue: [
      self writeBit: (charval bitAt: 9).
      ].
   ]  
   loadCharFreq: freqtable [
      |ordChar|
      [self atEnd not] whileTrue: [
          ordChar := self next asInteger.
          freqtable incr: ordChar.
      ].
      ordChar = nil ifFalse: [
         freqtable incr: 256.
      ].
   ]

   loadTree [
      |stack prebit|
      stack := Stack new: 256.
      [self atEnd not] whileTrue: [
      prebit := self nextBit.
      prebit = 0 ifTrue: [
         |bit bitchar bitindex newleaf|   
         bitchar := 0.
         bitindex := 8.
         [bitindex ~= 0] whileTrue: [
            bit := self nextBit.
            bitchar := bitchar bitAt: bitindex put: bit.
            bitindex := bitindex - 1.
         ].
         newleaf := Leaf new: (bitchar asCharacter) count: 0.
         bitchar = 0 ifTrue: [
         bit := self nextBit.
            bit = 1 ifTrue: [
               newleaf := Leaf new: 256 count: 0.
            ].
         ].
         stack push: newleaf.
      ].
      prebit = 1 ifTrue: [
         |ltree rtree newtree|
         rtree := stack pop.
         stack size = 0 ifTrue: [
            self clearBits.
            ^ rtree
         ].
      ltree := stack pop.
      newtree := Tree new: ltree char 
      count: 0 left: ltree right: rtree.
      stack push: newtree.
         ].
       ].
     ]
     compressTo: outfile with: encodings [
     |key encode bit|
     [self atEnd not] whileTrue: [
        key := self next value.
        encode := encodings at: key.
        encode do: [:char |
        bit := char asBit.
        outfile writeBit: bit.
      ].
      ].
      encode := encodings at: 256.
      encode do: [:char |
      bit := char asBit.
      outfile writeBit: bit.
      ].
      outfile flushByte.
    ]

    deCompressTo: outfile with: tree [
        |bit ctree|
        ctree := tree.
        bit := 0.
        [bit ~= nil] whileTrue: [
           bit := self nextBit.
           bit = 0 ifTrue: [
              ctree := ctree left.
           ].
           bit = 1 ifTrue: [
           ctree := ctree right.
           ].
           (ctree isMemberOf: Leaf) ifTrue: [
           |char|
           ctree char = 256 ifTrue: [ ^ char ].
           char := Character value: ctree char asInteger.
           outfile nextPut: char.
           ctree := tree.
          ].
       ].
    ]
]

Object subclass: Name [
   |first last|
   first [^ first]
   last [^ last]
   Name class >> new [self shouldNotImplement]

   Name class >> new: last first: first [
      |result|
      result := super new.
      result setFirst: first setLast: last.
      ^ result.
   ]

   setFirst: myFirst setLast: myLast [
      first := myFirst.
      last := myLast.
   ]

   <= other [
      last = other last
         ifTrue: [^ first <= other first]
         ifFalse: [^ last <= other last].
   ]

   printOn: aStream [
      ^ aStream << last << ', ' << first.
   ]
]

|d c t u |

d_flag := false. "debug"
t_flag := false. "print current tree"
c_flag := false. "zip"
u_flag := false. "unzip"


"flag boolean trigger"
Smalltalk arguments: '-d -c -t -u'
do: [:opt :arg |
    (opt = $d) ifTrue: [
       d_flag := true.
      " stdout << '-dflag is on' << nl."
     ].
    (opt = $c) ifTrue: [
       c_flag := true.
      " stdout << '-cflag is on' << nl."
     ].
    (opt = $t) ifTrue: [
       t_flag := true.
      " stdout << '-tflag is on' << nl. "
     ].
    (opt = $u) ifTrue: [
       u_flag := true.
     "  stdout << '-uflag is on' << nl. "
     ].
].


"Print a character or its ASCII code."
Character extend [
   asBit [
   ^ self value bitAt: 1.
   ]
   isPrint [
   ^ ($! <= self) & (self <= $~)
   ]
   visible [
      self isPrint ifTrue: [^ self asString]
      ifFalse: [^ self asciiValue printStringRadix: 16]
   ]
]

"Stack object."
Object subclass: Stack [
   |theArray first item|
   Stack class >> new [
   self shouldNotImplement.
   ]
   Stack class >> new: size [
   |result|
   result := super new.
   result init: size.
   ^ result
   ]

   init: size [
   first := 0.
   theArray := Array new: size.
   ]
   size [
      ^ first.
   ]

   nl := Character nl.
   pop [
   "check to see if stack full"
   first = 0 ifTrue: [ 
   stderr << 'not enough items to push' << nl.
   ^ nil
   ].
   item := theArray at: first.
   first := first - 1.
   ^ item
   ]
   push: item [
   first := first + 1.
   "check to see if stack full"
   first > self size ifTrue: [
   ^ stderr << 'too many obj to push' << nl.
       ].
      theArray at: first put: item.
   ]
]

"Frequency table array object."
Object subclass: ZeroArray [
    |theArray|
    ZeroArray class >> new [
       self shouldNotImplement.
    ]
    ZeroArray class >> new: size [
       |result|
       result := super new.
       result init: size.
       ^ result
    ]
    init: size [
    theArray := Array new: size.
    ]
    size [
    ^ theArray size.
    ]
    at: index [
   ^ theArray at: index + 1.
   ]
      at: index put: value [
      ^ theArray at: index + 1 put: value.
   ]
   incr: index [
   (self at: index) isNil
   ifTrue: [ self at: index put: 0].
   self at: index put: (self at: index) + 1.
   ]
       keysAndValuesDo: aBlock [
       (0 to: (self size) - 1) do: [:index |
       aBlock value: index value: (self at: index).
       ]
   ]
]

"mackey implementation"
Object subclass: Leaf [
   |char count|
   char [ ^ char ]
   count [ ^ count ]
   Leaf class >> new [
   self shouldNotImplement
   ]
   Leaf class >> new: aChar count: aCount [
   |result|
   result := super new.
   result setChar: aChar andCount: aCount.
   ^result
   ]
   setChar: aChar andCount: aCount [
   char := aChar.
   count := aCount.
   ]
   <= other [
   ^ (count < other count)
   | ((count = other count) & (char <= other char))
   ]
   printBase: aStream [
   ^ aStream << self class << '(' << char << ',' << count
   ]
   printOn: aStream [
   (self printBase: aStream) << ')'.
   ]
   "postorder: visitor prefix: string["
   inorder: visitor prefix: string [
   visitor value: char value: string.
   ]
   writeIn: outfile [
   outfile writeBit: (0 bitAt: 1).
   outfile bitChar: self char.
   ]
]

"Leaf tree object."
Leaf subclass: Tree [
   |left right|
   left [ ^ left ]
   right [ ^ right ]
   Tree class >> new: aChar count: aCount [
   self shouldNotImplement
   ]
   Tree class >> new: aChar count: aCount left: aLeft right: aRight [
   |result|
   result := super new: aChar count: aCount.
   result setLeft: aLeft andRight: aRight.
   ^ result
   ]
   setLeft: aLeft andRight: aRight [
   left := aLeft.
   right := aRight.
   ]
   printOn: aStream [
   (self printBase: aStream) << ',' << left << ',' << right << ')'.
   ]
   inorder: visitor prefix: string [
   left inorder: visitor prefix: string, '0'.
   right inorder: visitor prefix: string, '1'.
   "left postorder: visitor prefix: string, '2'."
   "right postorder: visitor prefix: string, '2'."
   ]
   writeIn: outfile [
   left writeIn: outfile.
   right writeIn: outfile.
   outfile writeBit: (1 bitAt: 1).
   ]
]

"Set program arguments."
opts := (Smalltalk getArgv: 1).
filenameIn := (Smalltalk getArgv: 2).
filenameOut := (Smalltalk getArgv: 3).

"Check program usage."
Smalltalk arguments size < 2
ifTrue: [ 
    stderr << 'usage: ' << execname 
    << ' -dtcu infile [outfile]' << nl.
    ObjectMemory quit.
].

"Load frequency table."
opts =~ 't|c' ifMatched: [
freqtable := ZeroArray new: 257.
   [
        |infile|
        infile := FileStream open: filenameIn
        mode: FileStream read.
        infile loadCharFreq: freqtable.
        infile close.
   ] on: SystemExceptions.FileError do: [:signal |
      |errno|
      errno := File errno.
      stdout flush.
      stderr << execname << ': ' << filenameIn << ': '
      << signal messageText << nl.
      stderr flush.
   ].
].

"Load priority queue from frequency table."
opts =~ 't|c' ifMatched: [
        pqueue := SortedCollection new.
        freqtable keysAndValuesDo: [:key :val |
        (val notNil and: [val > 0]) ifTrue: [
        newLeaf := Leaf new: (key asCharacter) count: val.
        pqueue add: newLeaf.
        ]
   ].
   opts =~ 'd' ifMatched: [pqueue inspect.].
].

"Unload priority queue into Huffman tree."
opts =~ 't|c' ifMatched: [
   [pqueue notEmpty] whileTrue: [
      tree := pqueue removeFirst.
      pqueue size = 0 ifTrue: [^ tree].
      rtree := pqueue removeFirst.
      newTree := Tree new: tree char 
      count: (tree count + rtree count)
      left: tree right: rtree. 
      pqueue add: newTree.
    ].
   d_flag ifTrue: [stdout << tree << nl.].
].

"tree traversal"
opts =~ 't|c' ifMatched: [
   encodings := ZeroArray new: 257.  
   tree = nil ifFalse: [
   tree inorder: [:char :encoding |
   encodings at: char asInteger put: encoding.
   ] prefix: ''.
   ].
].

"print tree"
t_flag ifTrue: [
   freqtable keysAndValuesDo: [:key :val |
   (val notNil and: [val > 0]) ifTrue: [
      |character|
      character := (key asCharacter visible).
      character asString size to: 3 do: [:skip| stdout << ' '].
      stdout << character << ' '. 
      val asString size to: 5 do: [:skip| stdout << ' '].
      stdout << val << ' '.
      stdout << (encodings at: key) << nl.
      ]
   ]
].






"compression module"
c_flag ifTrue: [
   [
   "compression module triggered"
   |infile outfile|
   infile := FileStream open: filenameIn
   mode: FileStream read.
   filenameOut = nil
   ifTrue: [
   outfile := stdout.
   "stdout << 'outfile reached' <<nl."
    ]
    ifFalse: [
       outfile := FileStream open: filenameOut
       mode: FileStream write.
    ]. 
    tree = nil ifFalse: [
    tree writeIn: outfile.
    outfile writeBit: (1 bitAt: 1).
    stdout << nl.
    outfile flushByte.
    infile compressTo: outfile with: encodings.
    ]. 
    outfile close.
    infile close.
    ] on: SystemExceptions.FileError do: [:signal |
       |errno|
       errno := File errno.
       stdout flush.
       stderr << execname << ': ' << filenameOut << ': '
        << signal messageText << nl.
       stderr flush.
    ].
].

"decompression module"
u_flag ifTrue: [
    [
    |infile outfile|
    infile := FileStream open: filenameIn
    mode: FileStream read.
    tree := infile loadTree.
    tree = nil ifFalse: [
    filenameOut = nil
    ifTrue: [
    infile deCompressTo: stdout with: tree.
    ]
    ifFalse: [
    outfile := FileStream open: filenameOut
    mode: FileStream write.
    infile deCompressTo: outfile with: tree.
    outfile close.
    ].
    ].
       infile close.
    ] on: SystemExceptions.FileError do: [:signal |
    |errno| 
    errno := File errno.
    stdout flush.
    stderr << execname << ': ' << filenameIn << ': '
    << signal messageText << nl.
   stderr flush.
   ].
   opts =~ 'd' ifMatched: [stdout << tree << nl.].
].

