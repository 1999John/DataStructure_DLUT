import re
import turtle as tt

LEFT = False
RIGHT = True
def visit(root,t,posi,angle):
    tt.setheading(270)
    if posi==LEFT:
        t.left(angle)
        t.forward(100)
        t.right(angle)
        t.write(str(root['value']), font=("Times", 18, "bold"))
    if posi==RIGHT:
        t.right(angle)
        t.forward(100)
        t.left(angle)
        t.write(str(root['value']), font=("Times", 18, "bold"))
    if posi==None:
        t.write(str(root['value']),font=("Times",18,"bold"))
    # print(root['value'],end=',')

def cmp ( l1: list, l2: list ) -> bool:
    if len(l1) == len(l2):
        for i in l1:
            if i not in l2:
                return False
        for i in l2:
            if i not in l1:
                return False
        return True
    else:
        return False


def getTherightPosi ( prelist: list, inlist: list, root ) -> int:
    if inlist.count(root) == 1:
        return inlist.index(root)
    else:
        for k, i in enumerate(inlist):
            if i == root:
                if cmp(inlist[:k], prelist[1:k + 1]):
                    return k


def creat ( prelist: list, inlist: list, tree: dict ):
    if len(prelist) != len(inlist) or len(prelist) == 0:
        return
    else:
        root = prelist[0]
        posi = getTherightPosi(prelist, inlist, root)

        preleft = prelist[1:posi + 1]
        prerigth = prelist[posi + 1:]

        inleft = inlist[:posi]
        inright = inlist[posi + 1:]

        tree['value'] = root
        tree['leftChild'] = {}
        tree['rightChild'] = {}

        creat(preleft, inleft, tree['leftChild'])
        creat(prerigth, inright, tree['rightChild'])


# def inorder(root,visit):
#     if root.get('value',None) is not None:
#         inorder(root['leftChild'],visit)
#         visit(root)
#         inorder(root['rightChild'],visit)
#
# def postorder(root,visit):
#     if root.get('value',None) is not None:
#         postorder(root['leftChild'],visit)
#         postorder(root['rightChild'],visit)
#         visit(root)

def preorder(root,visit,posi:bool,t:tt.Turtle,angle):
    if root.get('value',None) is not None:
        visit(root,t,posi,angle)
        preorder(root['leftChild'],visit,LEFT,t.clone(),angle-8)
        preorder(root['rightChild'],visit,RIGHT,t.clone(),angle-8)

if __name__ == '__main__':
    tree = {}
    # prestr = input("input pre string seprete with ',':\n")
    # instr = input("input in string seprete with ',':\n")

    tt = tt.Turtle()
    tt.speed(10)
    tt.color('yellow')
    tt.penup()
    tt.setpos(0,100)
    tt.pendown()
    tt.pencolor("red")
    tt.setheading(270)
    prestr="A,B,E,C,D,F,G,H,I,J"
    instr = "E,B,C,D,A,F,H,I,G,J"

    # prestr = "10,9,1,3,8,10,6,7,11"
    # instr = "1,9,3,10,7,6,10,8,11"

    prelist = re.split('[ ,]', prestr)
    inlist = re.split('[ ,]', instr)

    creat(prelist, inlist, tree)

    v = visit
    print('先序遍历',end='\t')
    preorder(tree,v,None,tt,60)
    input()
    # print('\n中序遍历',end='\t')
    # inorder(tree,v)


