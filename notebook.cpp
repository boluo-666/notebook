#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

// 主题枚举
enum 主题 {
    浅色,
    深色
};

// 当前主题
主题 当前主题 = 浅色;

// 全文搜索功能
bool 全文搜索文件内容(const std::string& 文件路径, const std::string& 搜索文本) {
    std::ifstream 文件(文件路径);
    if (文件.is_open()) {
        std::string 行内容;
        while (std::getline(文件, 行内容)) {
            if (行内容.find(搜索文本) != std::string::npos) {
                文件.close();
                return true;
            }
        }
        文件.close();
    }
    return false;
}

// 文件保存功能
void 保存文件(const std::string& 文件路径, const std::string& 内容) {
    std::ofstream 文件(文件路径);
    if (文件.is_open()) {
        文件 << 内容;
        文件.close();
    }
}

// 文件打开功能（通过命令行参数）
void 通过命令行打开文件(int 参数数量, char* 参数列表[]) {
    if (参数数量 != 2) {
        std::cout << "使用方法: " << 参数列表[0] << " <文件路径>" << std::endl;
        return;
    }
    std::ifstream 文件(参数列表[1]);
    if (文件.is_open()) {
        std::string 行内容;
        while (std::getline(文件, 行内容)) {
            std::cout << 行内容 << std::endl;
        }
        文件.close();
    }
    else {
        std::cout << "文件 " << 参数列表[1] << " 未找到。" << std::endl;
    }
}

// 文件编辑功能
std::string 编辑文件(const std::string& 文件路径) {
    std::ifstream 输入文件(文件路径);
    std::string 内容;
    if (输入文件.is_open()) {
        std::string 行内容;
        while (std::getline(输入文件, 行内容)) {
            内容 += 行内容 + '\n';
        }
        输入文件.close();
    }

    std::cout << "当前内容:" << std::endl << 内容;
    std::cout << "输入新内容（在 Linux/Mac 上按 Ctrl+D 或在 Windows 上按 Ctrl+Z 结束输入）:" << std::endl;
    std::string 新内容;
    std::string 行;
    while (std::getline(std::cin, 行)) {
        新内容 += 行 + '\n';
    }

    if (!新内容.empty()) {
        保存文件(文件路径, 新内容);
        return 新内容;
    }
    return 内容;
}

// 主题切换功能
void 切换主题() {
    if (当前主题 == 浅色) {
        当前主题 = 深色;
        std::cout << "已切换到深色主题。" << std::endl;
    }
    else {
        当前主题 = 浅色;
        std::cout << "已切换到浅色主题。" << std::endl;
    }
}

// 测试代码
int main(int argc, char* argv[]) {
    std::string 文件路径 = "test.txt";

    // 测试全文搜索功能
    bool 搜索结果 = 全文搜索文件内容(文件路径, "test");
    std::cout << "搜索结果: " << (搜索结果 ? "找到" : "未找到") << std::endl;

    // 测试文件保存功能
    保存文件(文件路径, "初始内容");

    // 测试文件打开功能
    通过命令行打开文件(argc, argv);

    // 测试文件编辑功能
    std::string 编辑后的内容 = 编辑文件(文件路径);
    std::cout << "编辑后的内容:" << std::endl << 编辑后的内容;

    // 测试主题切换功能
    切换主题();
    切换主题();

    return 0;
}