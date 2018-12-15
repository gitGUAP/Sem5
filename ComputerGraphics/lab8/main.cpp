#include	"main.h"

osg::AnimationPath *createAnimationPath(double radius, double time)
{
    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
    path->setLoopMode(osg::AnimationPath::LOOP);

    unsigned int numSamples = 100;
    double delta_yaw = 2.0 * osg::PI / (static_cast<double>(numSamples) - 1.0);
    double delta_time = time / static_cast<double>(numSamples);

    for (unsigned int i = numSamples; i > 0; --i)
    {
        double yaw = delta_yaw * i;
        osg::Vec3d pos(sin(yaw),  cos(yaw), cos(yaw));
        osg::Quat rot(-yaw, osg::Z_AXIS);

        path->insert(delta_time * i, osg::AnimationPath::ControlPoint(pos, rot));
    }

    return path.release();
}


int main(int argc, char *argv[])
{
    (void) argc; (void) argv;
    std::vector<std::string> files;
    files.push_back("../data/cow.osg.0,0,9 0.rot");
    //files.push_back("../data/cow.osg");
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFiles(files);

    osg::ref_ptr<osg::MatrixTransform> preroot = new osg::MatrixTransform;
    preroot->addChild(model.get());

    osg::ref_ptr<osg::MatrixTransform> root = new osg::MatrixTransform;
    root->addChild(preroot.get());

    osg::ref_ptr<osg::AnimationPathCallback> apcb = new osg::AnimationPathCallback;
    apcb->setAnimationPath(createAnimationPath(50.0, 6.0));

    preroot->setUpdateCallback(apcb.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());

    return viewer.run();
}
