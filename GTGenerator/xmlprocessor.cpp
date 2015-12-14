#include "xmlprocessor.h"

// Standard includes
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>

// Xerces includes
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

// XSD Codesynthesis generated stubs includes
#include "Xml/rois.hxx"
#include "Xml/gtp.hxx"
#include "Xml/labels.hxx"

using namespace std;
using namespace XERCES_CPP_NAMESPACE;
using std::cerr;

#include <QDebug>
#include <QDir>

XMLProcessor::XMLProcessor()
{

}

XMLProcessor::~XMLProcessor()
{

}

void XMLProcessor::saveRoisToXML(QList<DiagramSceneInfo *> *scenesInfos, QString xmlPath, int paddingPx, QString videoName) {
	try {
		QFile *tmpfile = new QFile(xmlPath+".tmp");
		QFile *roisFile = new QFile(xmlPath);

		if (tmpfile->open(QFile::WriteOnly|QFile::Truncate)) {
			qDebug() << "created rois.xml" << endl;
			tmpfile->close();
		}	

		gtrois::frame_sequence f_s;
		gtrois gt;
		gt.video_name(videoName.toStdString());
		gt.padding_px(paddingPx);

		for(int i=0; i<scenesInfos->size(); i++) {
			frame f;
			frame::roi_sequence r_s;

			QList<DiagramROI*> *rois = scenesInfos->at(i)->rois;

			for(int j=0; j<rois->size(); j++) {
				roi r;
				r.id(j);
				r.x(rois->at(j)->getTpx());
				r.y(rois->at(j)->getTpy());
				r.brx(rois->at(j)->getBrx());
				r.bry(rois->at(j)->getBry());
				r.w(rois->at(j)->getWidth());
				r.h(rois->at(j)->getHeight());
				r.labeled(rois->at(j)->isLabeled());
				r.removed(rois->at(j)->isRemoved());
				r.automatic(rois->at(j)->isAutomatic());
				r.label(rois->at(j)->getLabel().toStdString());
				r.label_id(rois->at(j)->getLabelId());
				r.color(rois->at(j)->getColor().name().toStdString());
				r_s.push_back(r);
			}			

			f.roi(r_s);
			f.no(i+1);

			f_s.push_back(f);
		}

		gt.frame(f_s);						

		XMLPlatformUtils::Initialize ();

		{
			// Choose a target.
			//
			auto_ptr<XMLFormatTarget> ft;		  

			ft = auto_ptr<XMLFormatTarget> (new LocalFileFormatTarget (tmpfile->fileName().toStdString().c_str()));

			xml_schema::namespace_infomap map;		  
			map[""].schema = "Xml\\rois.xsd";
			gtrois_ (*ft, gt, map, "UTF-8");
		}

		if(roisFile->exists()) {
			QFile().remove(roisFile->fileName());			
		}

		QFile().rename(tmpfile->fileName(), roisFile->fileName());

		XMLPlatformUtils::Terminate ();
	} catch (const xml_schema::exception& e) {
		std::cerr << e << std::endl;
		return;
	}
}

void XMLProcessor::readRoisFromXML(QList<DiagramSceneInfo *> *scenesInfos, QString xmlPath) {	
	try {

		QFile *roisFile = new QFile(xmlPath);

		if(roisFile->exists()) {
			std::ifstream ifs (xmlPath.toStdString());
			auto_ptr<gtrois> gt = gtrois_ (ifs);
			ifs.close ();

			for(gtrois::frame_sequence::iterator f = gt->frame().begin(); f != gt->frame().end(); f++) {
				//qDebug() << "\tFrame Id: " << f->id().get() << endl;
				DiagramSceneInfo *info = scenesInfos->at(f->no().get() - 1);

				QList<DiagramROI*> *rois = info->rois;
				rois->clear();

				for(frame::roi_sequence::iterator r = f->roi().begin(); r != f->roi().end(); r++) {
					/*qDebug() << "\t\tRoi Id: " << r->id().get() << endl;
					qDebug() << "\t\tRoi tpx: " << r->tpx().get() << endl;
					qDebug() << "\t\tRoi tpy: " << r->tpy().get() << endl;
					qDebug() << "\t\tRoi brx: " << r->brx().get() << endl;
					qDebug() << "\t\tRoi bry: " << r->bry().get() << endl;
					qDebug() << "\t\tRoi width: " << r->width().get() << endl;
					qDebug() << "\t\tRoi height: " << r->height().get() << endl;
					qDebug() << "\t\tRoi automatic: " << r->automatic().get() << endl;
					qDebug() << "\t\tRoi labeled: " << r->labeled().get() << endl;
					qDebug() << "\t\tRoi removed: " << r->removed().get() << endl;
					qDebug() << "\t\tRoi label: " << QString::fromStdString(r->label().get()) << endl;*/

					DiagramROI * roi = new DiagramROI();
					roi->setFrameId(f->no().get() - 1);
					roi->setIndex(r->id().get());
					roi->setTpx(r->x().get());
					roi->setTpy(r->y().get());
					roi->setBrx(r->brx().get());
					roi->setBry(r->bry().get());
					roi->setWidth(r->w().get());
					roi->setHeight(r->h().get());
					roi->setAutomatic(r->automatic().get());
					roi->setLabeled(r->labeled().get());
					roi->setRemoved(r->removed().get());
					roi->setLabel(QString::fromStdString(r->label().get()));
					roi->setLabelId(r->label_id().get());

					QString textColor;

					if(r->color() != NULL) {
						textColor = QString::fromStdString(r->color().get());					
					}
				
					if(!textColor.isEmpty()) {
						roi->setColor(QColor(textColor));
					} else {
						roi->setColor(Qt::white);
					}

					rois->append(roi);
				}
			}
		}		
	} catch (const xml_schema::exception& e) {
		std::cerr << e << std::endl;
		return;
	}	
}

void XMLProcessor::saveLabelsToXML(QList<DiagramROILabel *> *labels, QString xmlPath) {
	try {
		QFile *tmpfile = new QFile(xmlPath+".tmp");
		QFile *labelsFile = new QFile(xmlPath);

		if (tmpfile->open(QFile::WriteOnly|QFile::Truncate)) {
			qDebug() << "created labels.xml.tmp" << endl;
			tmpfile->close();
		}

		gtlabels::label_sequence l_s;
		gtlabels gl;	

		for(int i=0; i<labels->size(); i++) {
			label l;			

			l.id(labels->at(i)->getId());
			l.name(labels->at(i)->getName().toStdString());
			l.color(labels->at(i)->getColor().name().toStdString());
			l.removed(labels->at(i)->isRemoved());

			l_s.push_back(l);
		}

		gl.label(l_s);

		XMLPlatformUtils::Initialize ();

		{
			// Choose a target.
			//
			auto_ptr<XMLFormatTarget> ft;

			qDebug() << "tmpfile->fileName()" << tmpfile->fileName() << endl;
			ft = auto_ptr<XMLFormatTarget> (new LocalFileFormatTarget (tmpfile->fileName().toStdString().c_str()));

			xml_schema::namespace_infomap map;
			map[""].schema = "Xml\\labels.xsd";
			gtlabels_ (*ft, gl, map, "UTF-8");
		}

		if(labelsFile->exists()) {
			QFile().remove(labelsFile->fileName());			
		}

		QFile().rename(tmpfile->fileName(), labelsFile->fileName());
		
		XMLPlatformUtils::Terminate ();
	} catch (const xml_schema::exception& e) {
		std::cerr << e << std::endl;
		return;
	}
}

void XMLProcessor::readLabelsFromXML(QList<DiagramROILabel *> *labels, QString xmlPath) {	
	try {
		QFile *labelsFile = new QFile(xmlPath);

		if(labelsFile->exists()) {
			std::ifstream ifs (xmlPath.toStdString());
			auto_ptr<gtlabels> gl = gtlabels_ (ifs);
			ifs.close();

			labels->clear();

			for(gtlabels::label_sequence::iterator l = gl->label().begin(); l != gl->label().end(); l++) {
				DiagramROILabel *label = new DiagramROILabel();

				label->setId(l->id().get());
				label->setName(QString::fromStdString(l->name().get()));
				label->setColor(QColor(QString::fromStdString(l->color().get())));
				label->setRemoved(l->removed().get());
						
				labels->append(label);
			}
		}		
	} catch (const xml_schema::exception& e) {
		std::cerr << e << std::endl;
		return;
	}
}

void XMLProcessor::saveGTProjectToXML(GTProject *project, QString xmlPath) {
	try {
		QFile *tmpfile = new QFile(xmlPath+".tmp");
		QFile *gtpFile = new QFile(xmlPath);

		if (tmpfile->open(QFile::WriteOnly|QFile::Truncate)) {
			qDebug() << "created PROJECT_NAME.gtp.tmp" << endl;
			tmpfile->close();
		}		
		
		gtproj::proj_sequence p_s;
		gtproj gpj;

		proj p;
		p.name(project->name.toStdString());
		p.frame_count(project->frameCount);
		p.label_count(project->labelCount);
		p.video_source_path(project->videoSourcePath.toStdString());
		p.subsampling_enabled(project->subsamplingEnabled);
		p.subsampling_value(project->subsamplingValue);
		p.subsampling_step(project->subsamplingStep);
		p.bgs_iterations(project->bgsIterations);
		p.bgs_computed(project->bgsComputed);
		p.bgs_loaded(project->bgsLoaded);
		p.descriptors_computed(project->descriptorsComputed);

		p_s.push_back(p);

		gpj.proj(p_s);

		XMLPlatformUtils::Initialize ();

		{
			// Choose a target.
			//
			auto_ptr<XMLFormatTarget> ft;

			qDebug() << "tmpfile->fileName()" << tmpfile->fileName() << endl;
			ft = auto_ptr<XMLFormatTarget> (new LocalFileFormatTarget (tmpfile->fileName().toStdString().c_str()));

			xml_schema::namespace_infomap map;
			map[""].schema = "Xml\\gtp.xsd";
			gtproj_ (*ft, gpj, map, "UTF-8");
		}

		if(gtpFile->exists()) {
			QFile().remove(gtpFile->fileName());			
		}

		QFile().rename(tmpfile->fileName(), gtpFile->fileName());
		
		XMLPlatformUtils::Terminate ();
	} catch (const xml_schema::exception& e) {
		std::cerr << e << std::endl;
		return;
	}
}

void XMLProcessor::readGTProjectFromXML(GTProject *project, QString xmlPath) {
	try {
		QFile *gtpFile = new QFile(xmlPath);

		if(gtpFile->exists()) {
			std::ifstream ifs (xmlPath.toStdString());
			auto_ptr<gtproj> gtp = gtproj_ (ifs);
			ifs.close();
		
			proj g = gtp->proj()[0];

			project->name = QString::fromStdString(g.name().get());
			project->frameCount = g.frame_count().get();
			project->labelCount = g.label_count().get();
			project->videoSourcePath = QString::fromStdString(g.video_source_path().get());
			project->subsamplingEnabled = g.subsampling_enabled().get();
			project->subsamplingValue = g.subsampling_value().get();
			project->subsamplingStep = g.subsampling_step().get();
			project->bgsComputed = g.bgs_computed().get();
			project->bgsLoaded = g.bgs_loaded().get();
			project->bgsIterations = g.bgs_iterations().get();
			project->descriptorsComputed = g.descriptors_computed().get();
		}		
	} catch (const xml_schema::exception& e) {
		std::cerr << e << std::endl;
		return;
	}
}
