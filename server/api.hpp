#ifndef API_HPP_INCLUDED
#define API_HPP_INCLUDED

#include "../lib/SimpleREST/restful.hpp"
#include "database.hpp"
#include "database/statements.hpp"

#include <mutex>

namespace Carbonide { namespace Server {

    template <typename DatabaseT>
    class ApiSetup
    {
    public:
        ApiSetup(Rest::InterfaceProvider* app, DatabaseT* database)
            : app_(app)
            , database_(database)
        {

        }

        /**
         *  Registers all RESTful Service calls and prepares all statements.
         */
        void setup()
        {
            std::call_once(setupLock_, [&, this]{

                using namespace Database::Statements;
                using namespace Rest;

                // interface
                app_->get("/test", [](Request req, Response res)
                {
                    res.status(200).send("Hello");
                });

                app_->get("/add_user/:name", [this](Request req, Response res)
                {
                    addUser(*database_, req.getParameter("name"));
                    res.sendStatus(200);
                });

            });
        }

        /**
         *  Starts database and server.
         */
        void start()
        {
            database_->start();
            database_->setup();
            app_->start();
        }

        /**
         *  Stops server and database.
         */
        void stop()
        {
            database_->stop();
            app_->stop();
        }

    private:
        Rest::InterfaceProvider* app_;
        DatabaseT* database_;

        std::once_flag setupLock_;
    };
} // namespace Server
} // namespace Carbonide

#endif // API_HPP_INCLUDED
