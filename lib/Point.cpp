#include "Point.hpp"

Point::Point(int pid, std::string headerLine, std::string line, std::pair<int,int> xyCols)
{
    this->point_id = pid;
    this->setHeaders(headerLine);
    this->setData(line);
    this->setXY(xyCols);
}

int Point::getClusterId() const
{
    return this->cluster_id;
}

std::vector<std::string> Point::getHeaders() const
{
    return this->pointData.headers;
}

std::vector<std::string> Point::getData() const
{
    return this->pointData.childData;
}

std::pair<double, double> Point::getXY() const
{
    return this->xy;
}

void Point::setClusterId(int cid)
{
    this->cluster_id = cid;
}

/***********************************************************************************
**Function : setXY
**Description : set the XY target values for a given point
**Parameters : pair of int that reference x y cols in csv file
**Pre-Conditions : 
**Post-Conditions : point xy will contain data from respective xy col
**********************************************************************************/
void Point::setXY(std::pair<int, int> xy_Cols)
{
    std::pair <double, double> xyData;  //store here
    double x, y;    //to cast
    try {
        x = boost::lexical_cast<double>(this->pointData.childData.at(xy_Cols.first));
    }
    catch (const boost::bad_lexical_cast& e) {
        std::cout << "Exception Caught: " << e.what() << std::endl;
        std::cout << "x: " << this->pointData.childData.at(xy_Cols.first) << std::endl;
        std::cout << "Setting to default: 0.0" << std::endl;
        x = 0.0;
    }
    try {
        y = boost::lexical_cast<double>(this->pointData.childData.at(xy_Cols.second));
    }
    catch (const boost::bad_lexical_cast& e) {
        std::cout << "Exception Caught: " << e.what() << std::endl;
        std::cout << "y: " << this->pointData.childData.at(xy_Cols.second) << std::endl;
        std::cout << "Setting to default: 0.0" << std::endl;
        y = 0.0;
    }
    auto xyPair = std::make_pair(x,y);
    this->xy = xyPair;
}

/***********************************************************************************
**Function : setHeaders
**Description : set the header data of a given point
**Parameters : header line
**Pre-Conditions : null header data
**Post-Conditions : point will have attribute identifiers (header data)
**********************************************************************************/
void Point::setHeaders(std::string hLine)
{
    typedef boost::escaped_list_separator<char> Separator;
    typedef boost::tokenizer<Separator> Tokenizer;
    Tokenizer tokenizer(hLine);
    utils nUtility;
    for (auto&& p : tokenizer) {
        std::string h = nUtility.removeTrailingZeros(p);
        this->pointData.headers.push_back(h);
    }
}

void Point::setData(std::string dLine)
{
    typedef boost::escaped_list_separator<char> Separator;
    typedef boost::tokenizer<Separator> Tokenizer;
    Tokenizer tokenizer(dLine);
    utils nUtility;
    for (auto&& p : tokenizer) {
        std::string h = nUtility.removeTrailingZeros(p);
        this->pointData.childData.push_back(h);
    }
}


/***********************************************************************************
**Function : printPointAttributes
**Description : depending on implementation, can print attributes of a given point
**Parameters : none
**Pre-Conditions :
**Post-Conditions :
**********************************************************************************/
void Point::printPointAttributes()
{
    //at the moment this will not be human readable until we port to user interface
    //my idea is for user to be able to click on point which will give data
    //can also give flexibility for query language implementations.
    
    for (const auto& t : this->pointData.headers) {
        std::cout << t << '\t';
    }
    std::cout << std::endl;
    for (const auto& t : this->pointData.childData) {
        std::cout << t << '\t';
    }
    /*
    auto calcDAT = this->getXY();
    std::cout << calcDAT.first << "\t" << calcDAT.second << std::endl;
    */
}