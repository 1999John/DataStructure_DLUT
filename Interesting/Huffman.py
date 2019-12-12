def mysort(arr:list):
    for i in range(len(arr)):
        for j in range(len(arr)):
            if arr[i]<=arr[j]:
                arr[i],arr[j] = arr[j],arr[i]


class HuffmanTreeNode:

    def __init__ ( self, value_weight: tuple ) -> None:
        self.value_weight = value_weight
        self.parent: HuffmanTreeNode = None
        self.leftChild: HuffmanTreeNode = None
        self.rightChild: HuffmanTreeNode = None

    def __eq__ ( self, other ) -> bool:
        return self.value_weight[1] == other.value_weight[1]

    def __ne__ ( self, other ) -> bool:
        return self.value_weight[1] != other.value_weight[1]

    def __ge__ ( self, other ):
        return self.value_weight[1] >= other.value_weight[1]

    def __le__ ( self, other ):
        return self.value_weight[1] <= other.value_weight[1]

    def __getitem__ ( self, item ):
        return self.value_weight[item]

    def __str__ ( self ) -> str:
        return str(self.value_weight)


class HuffmanTree:

    def __init__ ( self, seq=None,value_weight:list=None) -> None:
        self.root: HuffmanTreeNode = HuffmanTreeNode(('NaN',0))

        if value_weight is None:
            self.value_weight = []
        else:
            self.value_weight = [HuffmanTreeNode(i) for i in value_weight]
        self.seq = seq
        if self.seq is not None:
            self._value_weightList()
        self._buildHuffmanTree()
        self.coding={}
        self._tree_to_dict(self.root,"")

    def _value_weightList ( self ):
        seqlist = list(self.seq)
        seq_set = set(seqlist)

        for i in seq_set:
            self.value_weight.append(HuffmanTreeNode((i, seqlist.count(i))))

    def _merge ( self, hto, htt, ht: HuffmanTreeNode ):

        hto.parent = ht
        htt.parent = ht

        ht.leftChild = hto
        ht.rightChild = htt

        ht.value_weight = ('NaN', hto.value_weight[1] + htt.value_weight[1])



    def _buildHuffmanTree ( self ):
        nodelist = self.value_weight[:]


        while len(nodelist) != 0:
            parent = HuffmanTreeNode(('NaN', 0))
            if len(nodelist)==1:
                par = nodelist[0]
                self.root.value_weight = par.value_weight
                self.root.leftChild  = par.leftChild
                self.root.rightChild = par.rightChild
                break
            mysort(nodelist)

            htn1, htn2 = nodelist[0], nodelist[1]


            self._merge(htn1, htn2, parent)

            self.root.value_weight = parent.value_weight
            self.root.leftChild = parent.leftChild
            self.root.rightChild = parent.rightChild

            nodelist.remove(htn1)
            nodelist.remove(htn2)
            nodelist.append(parent)

    def _tree_to_dict( self,root:HuffmanTreeNode,s ):
        if root is not 'NaN' and root is not None:
            if root.leftChild.value_weight[0] is 'NaN':
                self._tree_to_dict(root.leftChild,s+'0')
            else:
                self.coding[root.leftChild.value_weight[0]] = s+'0'
            if root.rightChild.value_weight[0] is 'NaN':
                self._tree_to_dict(root.rightChild,s+'1')
            else:
                self.coding[root.rightChild.value_weight[0]] = s+'1'

    def Encoding( self ,seq):
        ret = ""
        for i in seq:
            if i not in self.coding:
                raise Exception('没有对应的码')
            else:
                ret+=self.coding[i]
        return ret


    def Decoding( self,seq ):
        ret = ""
        current = self.root
        for i in seq:
            if i =='1':
                current = current.rightChild
                if current.rightChild is None:
                    ret+=current.value_weight[0]
                    current = self.root
            elif i=='0':
                current = current.leftChild
                if current.leftChild is None:
                    ret+= current.value_weight[0]
                    current = self.root
            else:
                raise Exception("解码错误")
        return ret

    def __str__ ( self ) -> str:
        return str(self.coding)

    def __getitem__(self, item):
        return self.coding[item]


if __name__=='__main__':
    s = """The Zen of Python, by Tim Peters\nBeautiful is better than ugly.\nExplicit is better than implicit.\nSimple is better than complex.\nComplex is better than complicated.\nFlat is better than nested.\nSparse is better than dense.\nReadability counts.\nSpecial cases aren't special enough to break the rules.\nAlthough practicality beats purity.\nErrors should never pass silently.\nUnless explicitly silenced.\nIn the face of ambiguity, refuse the temptation to guess.\nThere should be one-- and preferably only one --obvious way to do it.\nAlthough that way may not be obvious at first unless you're Dutch.\nNow is better than never.\nAlthough never is often better than *right* now.\nIf the implementation is hard to explain, it's a bad idea.\nIf the implementation is easy to explain, it may be a good idea.\nNamespaces are one honking great idea -- let's do more of those!\n"""
    h = HuffmanTree(seq=None,value_weight=[('B', 1), ('f', 11), ('*', 2), ('m', 16), ('u', 20), ('C', 1), ('R', 1), ('h', 31), ('.', 18), ('U', 1), ('d', 16), ('x', 6), ('r', 32), ('T', 3), ('!', 1), ('b', 20), ('S', 3), ('s', 43), ('F', 1), ('t', 76), ("'", 4), ('e', 90), ('Z', 1), ('y', 17), ('g', 11), ('I', 3), (',', 4), ('A', 3), ('v', 5), ('l', 33), ('-', 6), ('c', 16), ('o', 43), ('\n', 20), ('i', 50), ('w', 4), ('N', 2), ('k', 2), (' ', 124), ('P', 2), ('E', 2), ('p', 20), ('n', 40), ('a', 50), ('D', 1)])
    print(h)
    try:
        en = h.Encoding(s)
        with open(r"en.txt",'w') as f:
            f.write(en)
    except Exception as e:
        print(e)
    try:
        de = h.Decoding("10010100100110101011101000011010000010100110010101011101001011110001111100110011000011100101101000111110001011001010001111100001011101001010101111010110010110001001101001110010100000010111101110010100001011011101011101101010001101011111111010110011011111100111000000010100010001011110111110001110100010011010010010010001110111101101111101010111111110101110110101000110101111111101011001101111110011100000001010111110000111011110110111110101011111111110100010010010101011111000011101111011010101011101101010001101011111111010110011011111100111000000010111010100111100001110111101101010010001110100010011010011110011110000111011110110101001000101011101101010001101011111111010110011011111100111000000010111010100111100001110111101101111101011000111101011000111101000100110100000011011100011111010111011010100011010111111110101100110111111001110000000101000001001101111010110001111010001001001010111101110001100101100101010111011010100011010111111110101100110111111001110000000101110001010000001100101110100010011010011000101000110001100000011011111011011111111110001011101010011000100000111101101110100010010010101111011010110101011110001101110111010110000110010011010110001100101000001110010011111010110111011010110101011110001101110101000000011000100010111001110111110011101000111100101010001110011101011111100110101011100100010110110100110111010001001110011111101111111001100110001000101110011101111011110011000110101111101111101011000110110111111111100010100011010100011110110101111011000101100101111111111000111010001001101001001100111001001111001011010101101001100110001011011110001101000001011100110010110011011110111000011001101010110011111011010000011111101111100011101000100110100110100001101101001100110101010100100011101111011011111010101111111110111110001010110011111011010000011010101011000111101000100100101100000101111110011010101001010100011010101010100110010101011000110000000110111001011000100111111111100011100101101110010100010100001001100101011111100110101011111010110000111011111110001111011100110000101111100111010010110001001001100110111010001001001010010011010110010101010110100110011000101101111000110100011010101001100000101001001100100110110000000110001101111011110010100010100101100110000001111011111000101001100001101111100010100110000010101100100110010010011000111110011001110011000100110101110100011000111000101111100111011100010011101011111111110100010011100111111011111110011001100010001011100111011111100111000111110111010001100011100010111000010001110001010000001111111010001101010100110001111100110011100110001001101011000111110100101001111100101101111101000100000110110100110011010111100000110001011100100110010101011101000010000101111110101100111110100010010010111100111101000110101110110101000110101111111101011001101111110011100000001010000010111001100101100111101000100111001111110111111100110011000100010111001110100000101110011001011001101011101101010011001010111101000001010001101011111111010110011011111100111000000010110010111011001011100101110011111110010111010100000011110100011110100010010010110001010101111110011010101011111000011101111011010110000010000011111000111101110011000010101110110101100111000110011100011011111001110101010010001110111101110000111000011100101101011111111110010001101011000101000111000110001101011111000101010001110100010010010110001010101111110011010101011111000011101111011010110000010000011111000111101110011000010101110110101010100001101110001011111001110101010010001110111101110000111000011100101101011111111011100001000111000101000110101011000101001011001100111100011010111110001010100011101000100100101111100011000001001101110111000110101010011010110001100101010100110000010101100110011000011100111001110000001011101001011110010101000111110101111100010101000101100100110010011011101101011111110010001101011100010011101110000001111001010101001100101010111111001100110110010110100000100100")
        print(de)
    except Exception as e:
        print(e)


    while True:
        ans = input()
        print(h[ans])