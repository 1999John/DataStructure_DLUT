import re
import turtle as tt
LEFT = False
RIGHT = True

def draw(root,t,posi,angle,length):
    tt.setheading(270)
    if posi==LEFT:
        t.left(angle)
        t.forward(length)
        t.right(angle)
        t.write(str(root['value']), font=("Times", 18, "bold"))
    if posi==RIGHT:
        t.right(angle)
        t.forward(length)
        t.left(angle)
        t.write(str(root['value']), font=("Times", 18, "bold"))
    if posi==None:
        t.write(str(root['value']),font=("Times",18,"bold"))

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


def getTherightPosi ( inlist: list, postlist: list, root ) -> int:
    if inlist.count(root) == 1:
        return inlist.index(root)
    else:
        for k, i in enumerate(inlist):
            if i == root:
                if cmp(inlist[:k], postlist[:k]):
                    return k


def creat ( inlist: list, postlist: list, tree: dict ):
    if len(postlist) != len(inlist) or len(postlist) == 0:
        return
    else:
        root = postlist[-1]

        posi = getTherightPosi(inlist,postlist,root)

        inleft = inlist[:posi]
        inright = inlist[posi + 1:]

        postleft = postlist[:posi]
        postright = postlist[posi:-1]

        tree['value'] = root
        tree['leftChild'] = {}
        tree['rightChild'] = {}

        creat(inleft, postleft, tree['leftChild'])
        creat(inright, postright, tree['rightChild'])

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

def pic(root,visit,posi:bool,t:tt.Turtle,angle,length):
    if root.get('value',None) is not None:
        draw(root,t,posi,angle,length)
        pic(root['leftChild'],visit,RIGHT,t.clone(),angle-10,length-10)
        pic(root['rightChild'],visit,LEFT,t.clone(),angle-10,length-10)

if __name__ == '__main__':
    tree = {}

    # instr = input("input in string seprete with ',':")
    # poststr = input("input post string seprete with ',':")


    instr = "2,3,5,7,9,12,14,17,18,28,30,50,53,60,63"
    poststr = "2,3,7,5,12,9,17,18,30,53,63,60,50,28,14"

    tt = tt.Turtle()
    tt.speed(10)
    tt.color('yellow')
    tt.penup()
    tt.setpos(0,100)
    tt.pendown()
    tt.pencolor("red")
    tt.setheading(270)

    # prestr="10,9,7,6,8,5,3,4"

    # instr = "7,9,6,10,3,5,8,4"

    # poststr="7,6,9,3,5,4,8,10"

    # prestr = "10,9,1,3,8,10,6,7,11"



    postlist = re.split('[ ,]', poststr)
    inlist = re.split('[ ,]', instr)

    creat(inlist, postlist, tree)

    v = draw

    # print('中序遍历',end='\t')

    # inorder(tree,v)

    # print('\n后序遍历',end='\t')

    # postorder(tree,v)

    pic(tree,v,None,tt,60,100)
    input()
    tt.down()