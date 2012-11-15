/*
 * Copyright (C) 2012  Fernando García  <fernando.garli@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
   
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SGAPPLICATION_HXX
#define __SGAPPLICATION_HXX

#include <string>

#include <simgear/misc/sg_path.hxx>
#include <simgear/props/props.hxx>
#include <simgear/structure/SGSharedPtr.hxx>
#include <simgear/structure/subsystem_mgr.hxx>

/**
 * \brief Defines a base application class.
 *
 * This class is intended to be derived to another type of application. For
 * example, if you want an OSG based application, you can derive this class and
 * name yours SGOSGApplication.
 *
 * This class throws exceptions for error handling. It is recommended
 * that you place all the SGApplication stuff inside a try-catch.
 */
class SGApplication {
public:

    /**
     * This constructor performs all the SGApplication initialization code.
     * It is recommended that the inherited class implements init() so the
     * constructor just calls that function.
     *
     * Don't forget to call this constructor from the derived class.
     *
     * \param appname Application name.
     * \param datadir_required Whether the data directory is required by the
     *        program.
     */
    SGApplication(const char *appname, bool datadir_required = true);

    virtual ~SGApplication();

    /**
     * \brief Runs the main application loop.
     *
     * This function should be called from outside the derived class, from
     * main() for example. To exit the loop, use the 'quit' function.
     *
     * If you need another type of main loop, just implement this function in
     * your derived class (calling this one from your implementation is not
     * recommended, nor useful).
     */
    virtual void run();

    /**
     * \brief Quits the application.
     *
     * This should be called when you want to exit the application, instead of
     * making 'm_quit_flag' true. This allows other stuff to be done here.
     *
     * Don't forget to call this function from your derived class if you plan
     * adding custom stuff.
     */
    virtual void quit();

    /**
     * Gets a node from the application property tree. It just returns the node,
     * @see SGPropertyNode documentation to see how to access (or set) its
     * value.
     *
     * \param path Path to the node, relative to root.
     * \param create If the node should be created if it doesn't exist.
     * \return The node.
     */
    static SGPropertyNode *getNode(const char *path, bool create) {
        return m_property_tree->getNode(path, create);
    }

    SGSubsystemMgr *get_subsystem_mgr() {return m_subsystem_mgr;}

    SGSubsystem *get_subsystem(const char *name)
        {return m_subsystem_mgr->get_subsystem(name);}


    static std::string ROOTDIR;
protected:

    std::string m_appname;

    /**
     * Application will quit when this flag is true. It is recommended to use
     * the function quit() in order to quit the application.
     */
    bool                                m_quit_flag;

    /**
     * Target Frames Per Second. This value is taken from the property tree and
     * defined by the user.
     */
    double                              m_target_fps;

    /**
     * The subsystem manager. Controls the life cycle of every subsystem,
     * manages addition and removal of subsystems and keeps them always
     * accessible.
     */
    SGSharedPtr<SGSubsystemMgr>         m_subsystem_mgr;

    /**
     * The application property tree. It is a pointer to the root node. Also, it
     * is made static so even if by accident there are several SGApplication
     * objects, all of them share the same property tree.
     */
    static SGSharedPtr<SGPropertyNode>  m_property_tree;

    /**
     * \brief Initialization code should be placed here.
     *
     * Memory allocation and variable initialization should be placed in
     * constructor, other stuff should be here.
     *
     * This function is not called by SGApplication, so you need to call it
     * from a derived class, preferably in the end of the constructor, after
     * all memory allocation.
     */
    virtual void init() {}

    /**
     * Calculate the elapsed time between previous and current frames in
     * seconds. Also throttle FPS if desired. This is useful when limiting CPU
     * usage is a possibility (light and low power consuming programs for
     * example).
     *
     * \return Delta time in seconds.
     */
    double calculateDeltaTime();

    /**
     * \brief Check if the provided data directory exists.
     *
     * Useful when you want to determine if the user provided a correct data
     * directory location.
     *
     * This function is not called by default in SGApplication, you should call
     * it from your inherited class if you want to use it.
     */
    void checkDataDirectoryExists();
};

#endif // __SGAPPLICATION_HXX
