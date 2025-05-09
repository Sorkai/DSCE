#include <iostream>  // 用于标准输入输出 (cin, cout)
#include <queue>     // 用于层序遍历的队列
#include <stdexcept> // 用于标准异常 (例如 runtime_error)
#include <string>    // 在提示信息中使用
#include <limits>    // 用于 numeric_limits (处理输入错误)

// 模板化的二叉树节点结构体
template <typename T>
struct BiNode
{
    T data;
    BiNode<T> *lchild;
    BiNode<T> *rchild;

    // 构造函数
    BiNode(T val) : data(val), lchild(nullptr), rchild(nullptr) {}
};

// 模板化的二叉树类
template <typename T>
class BinaryTree
{
public:
    BiNode<T> *root;     // 二叉树的根节点
    T creation_sentinel; // 用于在创建树时表示空节点的哨兵值

    /**
     * @brief 构造函数
     * @param sentinel_for_input 用户定义的哨兵值，用于在输入时表示空节点。
     * 例如，对于char类型，可以是'#'；对于int类型，可以是-1（如果-1不是有效数据）。
     */
    BinaryTree(T sentinel_for_input) : root(nullptr), creation_sentinel(sentinel_for_input) {}

    /**
     * @brief 析构函数，释放二叉树占用的所有内存。
     */
    ~BinaryTree()
    {
        destroyRecursive(root);
    }

    /**
     * @brief 从标准输入（或指定的输入流）按前序序列创建二叉树。
     * @param in 输入流，默认为 std::cin。
     */
    void buildTreeFromPreorderInput(std::istream &in = std::cin)
    {
        std::cout << "\n开始构建二叉树 (数据类型: " << typeid(T).name() << "):" << std::endl;
        std::cout << "请按照前序遍历顺序输入节点数据。" << std::endl;
        std::cout << "当遇到空子树时，请输入哨兵值: '" << creation_sentinel << "'" << std::endl;
        std::cout << "例如，对于char类型和'#'哨兵: A B D # # E # # C # F # #" << std::endl;
        std::cout << "例如，对于int类型和-1哨兵: 10 5 3 -1 -1 7 -1 -1 15 -1 20 -1 -1" << std::endl;
        std::cout << "请输入根节点的值 (或哨兵值 '" << creation_sentinel << "' 表示空树): ";
        root = createRecursive(in);
        if (root == nullptr && typeid(T).name() == typeid(char).name() && creation_sentinel == T{'#'})
        {
            // Consume the rest of the line if only '#' was entered for an empty char tree
            // to prevent issues with subsequent inputs if not handled by caller.
            // This is a specific heuristic.
            std::string dummy;
            std::getline(in, dummy);
        }
    }

    /**
     * @brief 前序遍历二叉树。
     */
    void preOrderTraversal()
    {
        if (root == nullptr)
        {
            std::cout << "树为空。" << std::endl;
            return;
        }
        std::cout << "前序遍历: ";
        preOrderRecursive(root);
        std::cout << std::endl;
    }

    /**
     * @brief 层序遍历二叉树。
     */
    void levelOrderTraversal()
    {
        if (root == nullptr)
        {
            std::cout << "树为空。" << std::endl;
            return;
        }

        std::queue<BiNode<T> *> q;
        q.push(root);

        std::cout << "层序遍历: ";
        while (!q.empty())
        {
            BiNode<T> *currentNode = q.front();
            q.pop();
            std::cout << currentNode->data << " ";

            if (currentNode->lchild != nullptr)
            {
                q.push(currentNode->lchild);
            }
            if (currentNode->rchild != nullptr)
            {
                q.push(currentNode->rchild);
            }
        }
        std::cout << std::endl;
    }

private:
    /**
     * @brief 递归辅助函数，用于从输入流创建二叉树。
     * @param in 输入流。
     * @return 创建的子树的根节点指针，如果输入为哨兵值则返回 nullptr。
     */
    BiNode<T> *createRecursive(std::istream &in)
    {
        T val;
        if (!(in >> val))
        { // 尝试读取一个值
            std::cerr << "输入错误或提前结束。假设为空节点。" << std::endl;
            in.clear();                                                   // 清除错误标志
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略当前行剩余内容
            return nullptr;
        }

        if (val == creation_sentinel)
        {
            return nullptr; // 遇到哨兵值，表示空节点
        }

        BiNode<T> *newNode = new BiNode<T>(val); // 创建新节点
        // std::cout << "为节点 " << val << " 输入左孩子 (或 '" << creation_sentinel << "'): "; // 辅助提示，可按需开启
        newNode->lchild = createRecursive(in); // 递归创建左子树
        // std::cout << "为节点 " << val << " 输入右孩子 (或 '" << creation_sentinel << "'): "; // 辅助提示
        newNode->rchild = createRecursive(in); // 递归创建右子树
        return newNode;
    }

    /**
     * @brief 递归辅助函数，用于前序遍历。
     * @param node 当前节点。
     */
    void preOrderRecursive(BiNode<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        std::cout << node->data << " ";  // 访问根节点
        preOrderRecursive(node->lchild); // 遍历左子树
        preOrderRecursive(node->rchild); // 遍历右子树
    }

    /**
     * @brief 递归辅助函数，用于释放树的内存（后序方式）。
     * @param node 当前节点。
     */
    void destroyRecursive(BiNode<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        destroyRecursive(node->lchild);
        destroyRecursive(node->rchild);
        delete node;
    }
};

// 主函数 - 演示模板类的使用
int main()
{
    // 演示1: 使用 char 类型，哨兵值为 '#'
    std::cout << "****** 演示 Char 类型二叉树 ******" << std::endl;
    BinaryTree<char> charTree('#');        // 创建一个处理char的二叉树，哨兵是'#'
    charTree.buildTreeFromPreorderInput(); // 从标准输入构建树

    if (charTree.root)
    { // 检查树是否成功创建（非空）
        std::cout << "\nChar 类型树的根节点: " << charTree.root->data << std::endl;
        charTree.preOrderTraversal();
        charTree.levelOrderTraversal();
    }
    else
    {
        std::cout << "创建的 Char 类型树为空。" << std::endl;
    }
    std::cout << "***********************************" << std::endl;

    // 演示2: 使用 int 类型，哨兵值为 -1
    std::cout << "\n****** 演示 Int 类型二叉树 ******" << std::endl;
    BinaryTree<int> intTree(-1);          // 创建一个处理int的二叉树，哨兵是-1
    intTree.buildTreeFromPreorderInput(); // 从标准输入构建树

    if (intTree.root)
    { // 检查树是否成功创建（非空）
        std::cout << "\nInt 类型树的根节点: " << intTree.root->data << std::endl;
        intTree.preOrderTraversal();
        intTree.levelOrderTraversal();
    }
    else
    {
        std::cout << "创建的 Int 类型树为空。" << std::endl;
    }
    std::cout << "***********************************" << std::endl;

    // BinaryTree 对象在 main 函数结束时会自动调用析构函数释放内存

    return 0;
}
