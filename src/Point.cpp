#include "Point.hpp"

Point::Point(int pid, std::string headerLine, std::string line)
{
    this->point_id = pid;
    this->setHeaders(headerLine);
    this->setData(line);
}

// fix for parallel pushing... 
//not sure why boost does not like trivial constructor/destructor
/*
Point::Point(const Point & pObj)
{
    this->point_id = pObj.point_id;
    this->pointData.headers = pObj.pointData.headers;
    this->pointData.childData = pObj.pointData.childData;
}

Point::~Point()
{
}
*/

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

void Point::setXY(std::pair<int, int> xy_Cols)
{
    std::pair <double, double> xyData;  //store here
    double x, y;    //to cast
    try {
        x = boost::lexical_cast<double>(this->pointData.childData.at(xy_Cols.first));
        y = boost::lexical_cast<double>(this->pointData.childData.at(xy_Cols.second));
    }
    catch (const boost::bad_lexical_cast& e) {
        std::cout << "Exception Caught: " << e.what() << std::endl;
    }
    auto xyPair = std::make_pair(x,y);
    this->xy = xyPair;
}

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
}
