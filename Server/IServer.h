//
// Created by alon on 23/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_ISERVER_H
#define AP1_SEMETSER_PROJECT_ISERVER_H


class IServer {
public:
    virtual ~IServer() = default;

protected:
    virtual void stop() = 0;
    virtual void receive() = 0;
};


#endif //AP1_SEMETSER_PROJECT_ISERVER_H
