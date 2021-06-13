from typing import List


def partition(arr: List, left: int, right: int) -> int:
    base = arr[left]
    while left < right:
        while right > left and arr[right] >= base:
            right -= 1

        arr[left] = arr[right]

        while right > left and arr[left] <= base:
            left += 1

        arr[right] = arr[left]

    arr[left] = base
    return left


def quick_sort(arr, left, right):
    if left >= right:
        return None
    pivot = partition(arr, left, right)
    quick_sort(arr, left, pivot - 1)
    quick_sort(arr, pivot + 1, right)


def mysort(arr: List) -> None:
    # 对数组进行排序
    for i in range(len(arr)):
        for j in range(len(arr)):
            if arr[i] <= arr[j]:
                arr[i], arr[j] = arr[j], arr[i]
    # quick_sort(arr,0,len(arr)-1)


class HuffmanTreeNode:

    def __init__(self, value_weight: tuple) -> None:
        self.value_weight = value_weight
        self.parent: HuffmanTreeNode = None
        self.leftChild: HuffmanTreeNode = None
        self.rightChild: HuffmanTreeNode = None

    def __eq__(self, other) -> bool:
        return self.value_weight[1] == other.value_weight[1]

    def __ne__(self, other) -> bool:
        return self.value_weight[1] != other.value_weight[1]

    def __ge__(self, other):
        return self.value_weight[1] >= other.value_weight[1]

    def __le__(self, other):
        return self.value_weight[1] <= other.value_weight[1]

    def __getitem__(self, item):
        return self.value_weight[item]

    def __str__(self) -> str:
        return str(self.value_weight)


class HuffmanTree:

    def __init__(self, seq=None, value_weight: list = None) -> None:
        self.root: HuffmanTreeNode = HuffmanTreeNode(('NaN', 0))

        if value_weight is None:
            self.value_weight = []
        else:
            self.value_weight = [HuffmanTreeNode(i) for i in value_weight]

        self.seq = seq

        if self.seq is not None:
            self._value_weightList()

        self._buildHuffmanTree()
        self.coding = {}
        self._tree_to_dict(self.root, "")

    def _value_weightList(self):
        seqlist = list(self.seq)
        seq_set = set(seqlist)

        for i in seq_set:
            self.value_weight.append(HuffmanTreeNode((i, seqlist.count(i))))

    def _merge(self, hto, htt, ht: HuffmanTreeNode):

        hto.parent = ht
        htt.parent = ht

        ht.leftChild = hto
        ht.rightChild = htt

        ht.value_weight = ('NaN', hto.value_weight[1] + htt.value_weight[1])

    def _buildHuffmanTree(self):
        nodelist = self.value_weight[:]
        mysort(nodelist)
        while len(nodelist) != 0:
            parent = HuffmanTreeNode(('NaN', 0))
            if len(nodelist) == 1:
                par = nodelist[0]
                self.root.value_weight = par.value_weight
                self.root.leftChild = par.leftChild
                self.root.rightChild = par.rightChild
                break



            htn1, htn2 = nodelist[0], nodelist[1]

            self._merge(htn1, htn2, parent)

            self.root.value_weight = parent.value_weight
            self.root.leftChild = parent.leftChild
            self.root.rightChild = parent.rightChild

            nodelist.remove(htn1)
            nodelist.remove(htn2)
            self._nodelist_insert(nodelist,parent)

    def _nodelist_insert(self,nodelist:List,p:HuffmanTreeNode ):
        i = 0
        while i < len(nodelist) and p >= nodelist[i]:
            i += 1
        if i < len(nodelist):
            nodelist.insert(i,p)
        else:
            nodelist.append(p)
    def _tree_to_dict(self, root: HuffmanTreeNode, s):
        if root is not 'NaN' and root is not None:
            if root.leftChild.value_weight[0] is 'NaN':
                self._tree_to_dict(root.leftChild, s + '0')
            else:
                self.coding[root.leftChild.value_weight[0]] = s + '0'
            if root.rightChild.value_weight[0] is 'NaN':
                self._tree_to_dict(root.rightChild, s + '1')
            else:
                self.coding[root.rightChild.value_weight[0]] = s + '1'

    def Encoding(self, seq):
        ret = ""
        for i in seq:
            if i not in self.coding:
                raise Exception('没有对应的码')
            else:
                ret += self.coding[i]
        return ret

    def Decoding(self, seq):
        ret = ""
        current = self.root
        for i in seq:
            if i == '1':
                current = current.rightChild
                if current.rightChild is None:
                    ret += current.value_weight[0]
                    current = self.root
            elif i == '0':
                current = current.leftChild
                if current.leftChild is None:
                    ret += current.value_weight[0]
                    current = self.root
            else:
                raise Exception("解码错误")
        return ret

    def __str__(self) -> str:
        return str(self.coding)

    def __getitem__(self, item):
        return self.coding[item]


if __name__ == '__main__':
    s = """The Zen of Python, by Tim Peters\nBeautiful is better than ugly.\nExplicit is better than implicit.\nSimple is better than complex.\nComplex is better than complicated.\nFlat is better than nested.\nSparse is better than dense.\nReadability counts.\nSpecial cases aren't special enough to break the rules.\nAlthough practicality beats purity.\nErrors should never pass silently.\nUnless explicitly silenced.\nIn the face of ambiguity, refuse the temptation to guess.\nThere should be one-- and preferably only one --obvious way to do it.\nAlthough that way may not be obvious at first unless you're Dutch.\nNow is better than never.\nAlthough never is often better than *right* now.\nIf the implementation is hard to explain, it's a bad idea.\nIf the implementation is easy to explain, it may be a good idea.\nNamespaces are one honking great idea -- let's do more of those!\n"""
    h = HuffmanTree(seq=None,
                    value_weight=[('B', 1), ('f', 11), ('*', 2), ('m', 16), ('u', 20), ('C', 1), ('R', 1), ('h', 31),
                                  ('.', 18), ('U', 1), ('d', 16), ('x', 6), ('r', 32), ('T', 3), ('!', 1), ('b', 20),
                                  ('S', 3), ('s', 43), ('F', 1), ('t', 76), ("'", 4), ('e', 90), ('Z', 1), ('y', 17),
                                  ('g', 11), ('I', 3), (',', 4), ('A', 3), ('v', 5), ('l', 33), ('-', 6), ('c', 16),
                                  ('o', 43), ('\n', 20), ('i', 50), ('w', 4), ('N', 2), ('k', 2), (' ', 124), ('P', 2),
                                  ('E', 2), ('p', 20), ('n', 40), ('a', 50), ('D', 1)])
    print(h)
    try:
        en = h.Encoding(s)
        with open(r"en.txt", 'w') as f:
            f.write(en)
    except Exception as e:
        print(e)
    import time
    time.sleep(2)
    try:
        with open(r"en.txt",'r') as f:
            s = f.readlines()
        de = h.Decoding(s)
        print(de)
    except Exception as e:
        print(e)

    while True:
        ans = input()
        print(h[ans])
