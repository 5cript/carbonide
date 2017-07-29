#include "server.hpp"

namespace Carbonide { namespace Server
{
//#######################################################################################################
    CarbonideServer::CarbonideServer(Database::Database* database)
        //: app_(app)
        : database_(database)
    {

    }
//-------------------------------------------------------------------------------------------------------
    void CarbonideServer::setup()
    {
        std::call_once(setupLock_, [&, this]{

            //using namespace Rest;

/*
            // interface
            app_->get("/test", [](Request req, Response res)
            {
                res.status(200).send("Hello");
            });

            app_->get("/add_user/:name", [this](Request req, Response res)
            {
                res.sendStatus(200);
            });
*/

        });
    }
//#######################################################################################################
} // namespace Server
} // namespace Carbonide
