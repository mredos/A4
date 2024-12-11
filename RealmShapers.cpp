#include "RealmShapers.h"
#include <cmath>
#include <algorithm>

ShaperTree::ShaperTree()
{
    std::vector<RealmShaper *> realmShapers;
}

ShaperTree::~ShaperTree()
{
    // TODO: Free any dynamically allocated memory if necessary
    if(realmShapers.size() > 0) {
        for(int i = realmShapers.size()-1 ; i >= 0; i--) {
            delete realmShapers[i];
        }
    }

}

void ShaperTree::initializeTree(std::vector<RealmShaper *> shapers)
{
    // **************** COMPLETED *******************
    // TODO: Insert innitial shapers to the tree
    realmShapers = shapers;

    // *********************************************

}

int ShaperTree::getSize()
{
    // ************ COMPLETED ******************
    // TODO: Return number of shapers in the tree
    if(realmShapers.empty()) {
        return -1;
    }

    return realmShapers.size();

    // ***************************************
}

std::vector<RealmShaper *> ShaperTree::getTree()
{
    return realmShapers;
}

bool ShaperTree::isValidIndex(int index)
{
    bool isValid = false;

    if(index >= 0 && index < realmShapers.size()) {
        return true;
    }

    // TODO: Check if the index is valin in the tree

    return isValid;
}

void ShaperTree::insert(RealmShaper *shaper)
{
    // TODO: Insert shaper to the tree

    realmShapers.push_back(shaper);
}

int ShaperTree::remove(RealmShaper *shaper)
{
    // **************** COMPLETED ******************
    // TODO: Remove the player from tree if it exists
    // Make sure tree protects its form (complate binary tree) after deletion of a node
    // return index if found and removed
    // else

    for(int i = 0; i < realmShapers.size(); i++) {
        if(realmShapers[i] == shaper) {
            realmShapers.erase(realmShapers.begin() + i);
            return i;
        }
    }
    return -1;

    // ********************************************
}

int ShaperTree::findIndex(RealmShaper *shaper)
{
    // ************* COMPLETED *****************
    // return index in the tree if found
    int count{0};
    for (auto i : realmShapers) {
        if(shaper == i) {
            return count;
        }
        count += 1;
    }
    // else
    return -1;

    // ****************************************
}

int ShaperTree::getDepth(RealmShaper *shaper)
{
    // return depth of the node in the tree if found
    int index = findIndex(shaper);
    if (index == -1) {    // else
        return -1;
    }else {
        int depth = std::floor(std::log2(index + 1));
        return depth;
    }

}

int ShaperTree::getDepth()
{
    // return total|max depth|height of the tree
    if(realmShapers.empty()) {
        return 0;
    }else {
        int depth = std::floor(std::log2(getSize()));
        return depth;
    }
}

RealmShaper ShaperTree::duel(RealmShaper *challenger, bool result)
{
    // ****************************** COMPLETED ************************************
    // TODO: Implement duel logic, return the victor

    RealmShaper* parent = getParent(challenger);

    if(result) {
        parent->loseHonour();
        challenger->gainHonour();

        std::cout << "[Duel] " << challenger->getName() << " won the duel" << std::endl;
        std::cout << "[Honour] " << "New honour points: ";
        std::cout << challenger->getName() << "-" << challenger->getHonour() << " ";
        std::cout << parent->getName() << "-" << parent->getHonour() << std::endl;

        replace(challenger, parent);

        if(parent->getHonour() <= 0) {
            std::cout << "[Duel] " << parent->getName() << " lost all honour, delete" << std::endl;
            remove(parent);
        }

        return *challenger;

    }else {
        parent->gainHonour();
        challenger->loseHonour();

        std::cout << "[Duel] " << parent->getName() << " won the duel" << std::endl;
        std::cout << "[Honour] " << "New honour points: ";
        std::cout << challenger->getName() << "-" << challenger->getHonour() << " ";
        std::cout << parent->getName() << "-" << parent->getHonour() << std::endl;

        if(challenger->getHonour() <= 0) {
            std::cout << "[Duel] " << challenger->getName() << " lost all honour, delete" << std::endl;
            remove(challenger);
        }

        return *parent;
    }

    // **************************************************************************

}

RealmShaper *ShaperTree::getParent(RealmShaper *shaper)
{
    RealmShaper *parent = nullptr;

    // **************** COMPLETED *******************
    // TODO: return parent of the shaper

    double parentIndex;
    double shaperIndex;

    shaperIndex = findIndex(shaper);
    if(shaperIndex == 0) { // root

    }else if (shaperIndex > 0) { // notRoot
        parentIndex = std::floor((shaperIndex - 1) / 2);
        parent = realmShapers[parentIndex];
    }

    return parent;

    // **********************************************
}

void ShaperTree::replace(RealmShaper *player_low, RealmShaper *player_high)
{
    // ************** COMPLETED *******************
    // TODO: Change player_low and player_high's positions on the tree
    RealmShaper* temp = realmShapers[findIndex(player_low)];
    realmShapers[findIndex(player_low)] = realmShapers[findIndex(player_high)];
    realmShapers[findIndex(player_high)] = temp;
    // *******************************************

}

RealmShaper *ShaperTree::findPlayer(RealmShaper shaper)
{
    RealmShaper *foundShaper = nullptr;

    // ************* COMPLETED *****************
    // TODO: Search shaper by object
    // Return the shaper if found
    for(auto i : realmShapers) {
        if(*i == shaper) {
            foundShaper = i;
            break;
        }
    }
    // Return nullptr if shaper not found

    return foundShaper;

    // ****************************************
}

// Find shaper by name
RealmShaper *ShaperTree::findPlayer(std::string name)
{
    RealmShaper *foundShaper = nullptr;

    // **************** COMPLETED ******************
    // TODO: Search shaper by name
    // Return the shaper if found
    for(auto i: realmShapers) {
        if(i->getName() == name) {
            foundShaper = i;
            break;
        }
    }
    // Return nullptr if shaper not found

    return foundShaper;

    // ********************************************
}

// ***************** COMPLETED IN ORDER ***********************
void helperInOrder(std::vector<RealmShaper *> realmShapers,int index, std::vector<std::string> & refResult){
    if (index < realmShapers.size() && index >= 0) {
        helperInOrder(realmShapers, 2 * index + 1, refResult);
        refResult.push_back(realmShapers[index]->getName());
        helperInOrder(realmShapers, 2 * index + 2, refResult);
    }
    else{
        return;
    }
}

std::vector<std::string> ShaperTree::inOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement inOrderTraversal in tree
    // Add all to a string vector
    // Return the vector

    // Define and implement as many helper functions as necessary for recursive implementation
    helperInOrder(realmShapers, index, result);
    // Note: Since SheperTree is not an binary search tree,
    // in-order traversal will not give rankings in correct order
    // for correct order you need to implement level-order traversal
    // still you are to implement this function as well
    return result;
}
// **********************************************************

// ************** COMPLETED PREORDER ************************
void helperPreOrder(std::vector<RealmShaper *> realmShapers,int index, std::vector<std::string> & refResult){
    if (index < realmShapers.size() && index >= 0) {
        refResult.push_back(realmShapers[index]->getName());
        helperPreOrder(realmShapers, 2 * index + 1, refResult);
        helperPreOrder(realmShapers, 2 * index + 2, refResult);
    }
    else{
        return;
    }
}

std::vector<std::string> ShaperTree::preOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement preOrderTraversal in tree
    // Add all to a string vector
    // Return the vector

    helperPreOrder(realmShapers,index,result);

    return result;

    // Define and implement as many helper functions as necessary for recursive implementation

}
// **********************************************************

// **************** COMPLETED POSTORDER *********************

void helperPostOrder(std::vector<RealmShaper *> realmShapers,int index, std::vector<std::string> & refResult){
    if (index < realmShapers.size() && index >= 0) {
        helperPostOrder(realmShapers, 2 * index + 1, refResult);
        helperPostOrder(realmShapers, 2 * index + 2, refResult);
        refResult.push_back(realmShapers[index]->getName());
    }
    else{
        return;
    }
}

std::vector<std::string> ShaperTree::postOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement postOrderTraversal in tree
    // Add all to a string vector
    // Return the vector
    helperPostOrder(realmShapers, index, result);
    // Define and implement as many helper functions as necessary for recursive implementation
    return result;
}
// **********************************************************

void ShaperTree::preOrderTraversal(int index, std::ofstream &outFile)
{
    // TODO: Implement preOrderTraversal in tree
    // write nodes to output file

    // Define and implement as many helper functions as necessary for recursive implementation
}

void ShaperTree::breadthFirstTraversal(std::ofstream &outFile)
{
    // TODO: Implement level-order traversal
    // write nodes to output file

    // Define and implement as many helper functions as necessary
}

void ShaperTree::displayTree()
{
    std::cout << "[Shaper Tree]" << std::endl;
    printTree(0, 0, "");
}

// Helper function to print tree with indentation
void ShaperTree::printTree(int index, int level, const std::string &prefix)
{
    if (!isValidIndex(index))
        return;

    std::cout << prefix << (level > 0 ? "   └---- " : "") << *realmShapers[index] << std::endl;
    int left = 2 * index + 1;  // TODO: Calculate left index
    int right = 2 * index + 2; // TODO: Calculate right index

    if (isValidIndex(left) || isValidIndex(right))
    {
        printTree(left, level + 1, prefix + (level > 0 ? "   │   " : "")); // ╎
        printTree(right, level + 1, prefix + (level > 0 ? "   │   " : ""));
    }
}

void ShaperTree::writeShapersToFile(const std::string &filename)
{
    // TODO: Write the shapers to filename output level by level
    // Use std::cout << "[Output] " << "Shapers have been written to " << filename << " according to rankings." << std::endl;
}

void ShaperTree::writeToFile(const std::string &filename)
{
    // TODO: Write the tree to filename output pre-order
    // Use std::cout << "[Output] " << "Tree have been written to " << filename << " in pre-order." << std::endl;
}
