/*
Weather Client

You are going to develop a program that gets the statistics about weather in the current city
using information from a certain server. The goal is to calculate statistics using the data from weather server.

To communicate with the weather server you have to implement interface IWeatherServer,
which provides the raw string from the real server for the requested day and time.

The real server (i.e. "weather.com") gets the requests in this format:
"<date>;<time>", for example:
"31.08.2018;03:00"

The server answers on requests with string like this:
"20;181;5.1"
This string contains the weather for the requested time and means next:
"<air_temperature_in_celsius>;<wind_direction_in_degrees>:<wind_speed>".
Wind direction value may be in range from 0 to 359 inclusively, temperature may be negative.

The task:
1. Implement fake server, because interacting with real network is inacceptable within the unit tests.
To do this, you need to use real server responses. Fortunately, you've collected some results for the several dates from the weather server.
Each line means "<request>" : "<response>":

"31.08.2018;03:00" : "20;181;5.1"
"31.08.2018;09:00" : "23;204;4.9"
"31.08.2018;15:00" : "33;193;4.3"
"31.08.2018;21:00" : "26;179;4.5"

"01.09.2018;03:00" : "19;176;4.2"
"01.09.2018;09:00" : "22;131;4.1"
"01.09.2018;15:00" : "31;109;4.0"
"01.09.2018;21:00" : "24;127;4.1"

"02.09.2018;03:00" : "21;158;3.8"
"02.09.2018;09:00" : "25;201;3.5"
"02.09.2018;15:00" : "34;258;3.7"
"02.09.2018;21:00" : "27;299;4.0"

IMPORTANT:
* Server returns empty string if request is invalid.
* Real server stores weather only for times 03:00, 09:00, 15:00 and 21:00 for every date. Do not use other hours in a day.

2. Implement IWeatherClient using fake server.
*/

/**
 * Architecture:
 * The WeatherClient has to be able to send valid requests to the server, parse and store received responses.
 * So there has to be a struct (WeatherInfo) that contains parsed information and also the following functions:
 *
 * void GetWeatherInfoForDate(const std::string& date, std::vector<WeatherInfo>& weatherInfo)
 * WeatherInfo ParseResponse(const std::string& response)
 */

/**
 * Test plan:
 * 1. "20;181;5.1" -> ParseResponse -> {20, 181, 5.1}
 * 2. "23;204;4.9" -> ParseResponse -> {23, 204, 4.9}
 * 3. "31.08.2018" -> GetWeatherInfoForDate -> { {20, 181, 5.1}, {23, 204, 4.9}, {33, 193, 4.3}, {26, 179, 4.5} }
 * 4. "01.09.2018" -> GetWeatherInfoForDate -> { {19, 176, 4.2}, {22, 131, 4.1}, {31, 109, 4.0}, {24, 127, 4.1} }
 * 5. "31.08.2018" -> GetAverageTemperature -> 25.5
 * 6. "31.08.2018" -> GetMinimumTemperature -> 20
 * 7. "31.08.2018" -> GetMaximumTemperature -> 33
 * 8. "31.08.2018" -> GetAverageWindDirection -> 189.25
 * 9. "31.08.2018" -> GetMaximumWindSpeed -> 5.1
 * 10. "01.09.2018" -> GetAverageTemperature -> 24
 * 11. "01.09.2018" -> GetMinimumTemperature -> 19
 * 12. "01.09.2018" -> GetMaximumTemperature -> 31
 * 13. "01.09.2018" -> GetAverageWindDirection -> 135.75
 * 14. "01.09.2018" -> GetMaximumWindSpeed -> 4
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class IWeatherServer
{
public:
    virtual ~IWeatherServer() { }
    // Returns raw response with weather for the given day and time in request
    virtual std::string GetWeather(const std::string& request) = 0;
};

class WeatherServer : public IWeatherServer
{
public:
    ~WeatherServer() { }
    // Returns raw response with weather for the given day and time in request
    std::string GetWeather(const std::string& request)
    {
        if(request == "31.08.2018;03:00") return "20;181;5.1";
        if(request == "31.08.2018;09:00") return "23;204;4.9";
        if(request == "31.08.2018;15:00") return "33;193;4.3";
        if(request == "31.08.2018;21:00") return "26;179;4.5";
        if(request == "01.09.2018;03:00") return "19;176;4.2";
        if(request == "01.09.2018;09:00") return "22;131;4.1";
        if(request == "01.09.2018;15:00") return "31;109;4.0";
        if(request == "01.09.2018;21:00") return "24;127;4.1";
        return "";
    }
};

// Implement this interface
class IWeatherClient
{
public:
    virtual ~IWeatherClient() { }
    virtual double GetAverageTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMinimumTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMaximumTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetAverageWindDirection(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date) = 0;
};

struct WeatherInfo
{
    int temperature;
    int windDirection;
    double windSpeed;
};

bool operator==(const WeatherInfo& lhs, const WeatherInfo& rhs)
{
    return lhs.temperature == rhs.temperature
            && lhs.windDirection == rhs.windDirection
            && lhs.windSpeed == rhs.windSpeed;
}

class WeatherClient : public IWeatherClient
{
public:
    WeatherClient() { }

    virtual ~WeatherClient() { }

    WeatherInfo ParseResponse(const std::string& response)
    {
        std::string numbers = response;
        std::replace(numbers.begin(), numbers.end(), ';', ' ');
        std::istringstream iss(numbers);

        WeatherInfo result;
        iss >> result.temperature >> result.windDirection >> result.windSpeed;
        return result;
    }

    void GetWeatherInfoForDate(IWeatherServer& server, const std::string& date, std::vector<WeatherInfo>& weatherInfo)
    {
        for(auto time : { "03:00", "09:00", "15:00", "21:00" })
        {
            weatherInfo.push_back(
                ParseResponse(server.GetWeather(date + ";" + time))
            );
        }
    }

    double GetAverageTemperature(IWeatherServer& server, const std::string& date)
    {
        double result = 0;
        std::vector<WeatherInfo> weatherInfo;
        GetWeatherInfoForDate(server, date, weatherInfo);

        for (WeatherInfo& wi : weatherInfo)
        {
            result += wi.temperature;
        }

        return result / 4.;
    }

    double GetMinimumTemperature(IWeatherServer& server, const std::string& date)
    {
        std::vector<WeatherInfo> weatherInfo;
        GetWeatherInfoForDate(server, date, weatherInfo);

        double result = weatherInfo.front().temperature;
        for (int i = 1; i < 4; i++)
        {
            result = result < weatherInfo[i].temperature ? result : weatherInfo[i].temperature;
        }

        return result;
    }

    double GetMaximumTemperature(IWeatherServer& server, const std::string& date)
    {
        std::vector<WeatherInfo> weatherInfo;
        GetWeatherInfoForDate(server, date, weatherInfo);

        double result = weatherInfo.front().temperature;
        for (int i = 1; i < 4; i++)
        {
            result = result > weatherInfo[i].temperature ? result : weatherInfo[i].temperature;
        }

        return result;
    }

    double GetAverageWindDirection(IWeatherServer& server, const std::string& date)
    {
        double result = 0;
        std::vector<WeatherInfo> weatherInfo;
        GetWeatherInfoForDate(server, date, weatherInfo);

        for (WeatherInfo& wi : weatherInfo)
        {
            result += wi.windDirection;
        }

        return result / 4.;
    }

    double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date)
    {
        std::vector<WeatherInfo> weatherInfo;
        GetWeatherInfoForDate(server, date, weatherInfo);

        double result = weatherInfo.front().windSpeed;
        for (int i = 1; i < 4; i++)
        {
            result = result > weatherInfo[i].windSpeed ? result : weatherInfo[i].windSpeed;
        }

        return result;
    }
};

//"20;181;5.1" -> ParseResponse -> {20, 181, 5.1}
TEST(weatherClient, ParseResponse1)
{
    WeatherClient weatherClient;
    WeatherInfo expectedInfo = {20, 181, 5.1};
    ASSERT_EQ(expectedInfo, weatherClient.ParseResponse("20;181;5.1"));
}

//"23;204;4.9" -> ParseResponse -> {23, 204, 4.9}
TEST(weatherClient, ParseResponse2)
{
    WeatherClient weatherClient;
    WeatherInfo expectedInfo = {23, 204, 4.9};
    ASSERT_EQ(expectedInfo, weatherClient.ParseResponse("23;204;4.9"));
}

//"31.08.2018" -> GetWeatherInfoForDate -> { {20, 181, 5.1}, {23, 204, 4.9}, {33, 193, 4.3}, {26, 179, 4.5} }
TEST(weatherClient, GetWeatherInfoForDate1)
{
    WeatherServer weatherServer;
    WeatherClient weatherClient;

    std::vector<WeatherInfo> expectedInfo = { {20, 181, 5.1}, {23, 204, 4.9}, {33, 193, 4.3}, {26, 179, 4.5} };

    std::string date = "31.08.2018";
    std::vector<WeatherInfo> actualInfo;

    weatherClient.GetWeatherInfoForDate(weatherServer, date, actualInfo);

    ASSERT_EQ(actualInfo, expectedInfo);
}

//"01.09.2018" -> GetWeatherInfoForDate -> { {19, 176, 4.2}, {22, 131, 4.1}, {31, 109, 4.0}, {24, 127, 4.1} }
TEST(weatherClient, GetWeatherInfoForDate2)
{
    WeatherServer weatherServer;
    WeatherClient weatherClient;

    std::vector<WeatherInfo> expectedInfo = { {19, 176, 4.2}, {22, 131, 4.1}, {31, 109, 4.0}, {24, 127, 4.1} };

    std::string date = "01.09.2018";
    std::vector<WeatherInfo> actualInfo;

    weatherClient.GetWeatherInfoForDate(weatherServer, date, actualInfo);

    ASSERT_EQ(actualInfo, expectedInfo);
}

//"31.08.2018" -> GetAverageTemperature -> 25.5
TEST(weatherClient, GetAverageTemperature1)
{
    WeatherServer weatherServer;
    WeatherClient weatherClient;

    double expectedInfo = 25.5;
    std::string date = "31.08.2018";

    ASSERT_EQ(expectedInfo, weatherClient.GetAverageTemperature(weatherServer, date));
}

//"31.08.2018" -> GetMinimumTemperature -> 20
TEST(weatherClient, GetMinimumTemperature1)
{
    WeatherServer weatherServer;
    WeatherClient weatherClient;

    double expectedInfo = 20;
    std::string date = "31.08.2018";

    ASSERT_EQ(expectedInfo, weatherClient.GetMinimumTemperature(weatherServer, date));
}

//"31.08.2018" -> GetMaximumTemperature -> 33
TEST(weatherClient, GetMaximumTemperature1)
{
    WeatherServer weatherServer;
    WeatherClient weatherClient;

    double expectedInfo = 33;
    std::string date = "31.08.2018";

    ASSERT_EQ(expectedInfo, weatherClient.GetMaximumTemperature(weatherServer, date));
}

//"31.08.2018" -> GetAverageWindDirection -> 189.25
TEST(weatherClient, GetAverageWindDirection1)
{
    WeatherServer weatherServer;
    WeatherClient weatherClient;

    double expectedInfo = 189.25;
    std::string date = "31.08.2018";

    ASSERT_EQ(expectedInfo, weatherClient.GetAverageWindDirection(weatherServer, date));
}

//"31.08.2018" -> GetMaximumWindSpeed -> 5.1
TEST(weatherClient, GetMaximumWindSpeed1)
{
    WeatherServer weatherServer;
    WeatherClient weatherClient;

    double expectedInfo = 5.1;
    std::string date = "31.08.2018";

    ASSERT_EQ(expectedInfo, weatherClient.GetMaximumWindSpeed(weatherServer, date));
}

//"01.09.2018" -> GetAverageTemperature -> 24
TEST(weatherClient, GetAverageTemperature2)
{
    WeatherServer weatherServer;
    WeatherClient weatherClient;

    double expectedInfo = 24;
    std::string date = "01.09.2018";

    ASSERT_EQ(expectedInfo, weatherClient.GetAverageTemperature(weatherServer, date));
}
