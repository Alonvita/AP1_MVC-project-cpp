//
// Created by alon on 23/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_ISERVER_H
#define AP1_SEMETSER_PROJECT_ISERVER_H


class IServer {
public:
    virtual ~IServer() = default;

    virtual void receive() = 0;
    virtual void initSocket() = 0;

protected:
    virtual void stop() = 0;
};


#endif //AP1_SEMETSER_PROJECT_ISERVER_H
