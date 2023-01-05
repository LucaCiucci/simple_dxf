#pragma once

// ORIGINAL NOTICE: 
// ```
// dxf.h
// Copyright (c) 2009, Dan Heeks
// This program is released under the BSD license. See the file COPYING for details.
// modified 2018 wandererfan
// ```

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iosfwd>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

//#include <Base/Vector3D.h>
//#include <Mod/Import/ImportGlobal.h>
#include <algorithm>

#include <simple_dxf/vectors.hpp>

namespace simple_dxf
{
	typedef int Aci_t; // AutoCAD color index

	typedef enum
	{
		eUnspecified = 0,   // Unspecified (No units)
		eInches,
		eFeet,
		eMiles,
		eMillimeters,
		eCentimeters,
		eMeters,
		eKilometers,
		eMicroinches,
		eMils,
		eYards,
		eAngstroms,
		eNanometers,
		eMicrons,
		eDecimeters,
		eDekameters,
		eHectometers,
		eGigameters,
		eAstronomicalUnits,
		eLightYears,
		eParsecs
	} eDxfUnits_t;

	//spline data for reading
	struct SplineData
	{
		double norm[3];
		int degree;
		int knots;
		int control_points;
		int fit_points;
		int flag;
		std::list<double> starttanx;
		std::list<double> starttany;
		std::list<double> starttanz;
		std::list<double> endtanx;
		std::list<double> endtany;
		std::list<double> endtanz;
		std::list<double> knot;
		std::list<double> weight;
		std::list<double> controlx;
		std::list<double> controly;
		std::list<double> controlz;
		std::list<double> fitx;
		std::list<double> fity;
		std::list<double> fitz;
	};

	struct SplineDataOut
	{
		Vector3d norm;
		int degree;
		int knots;
		int control_points;
		int fit_points;
		int flag;
		Vector3d starttan;
		Vector3d endtan;
		std::vector<double> knot;
		std::vector<double> weight;
		std::vector<Vector3d> control;
		std::vector<Vector3d> fit;
	};

	struct LWPolyDataOut
	{
		double nVert;
		int    Flag;
		double Width;
		double Elev;
		double Thick;
		std::vector<Vector3d> Verts;
		std::vector<double> StartWidth;
		std::vector<double> EndWidth;
		std::vector<double> Bulge;
		Vector3d Extr;
	};

	class CDxfWrite {
	private:
		std::ofstream* m_ofs;
		bool m_fail;
		std::ostringstream* m_ssBlock;
		std::ostringstream* m_ssBlkRecord;
		std::ostringstream* m_ssEntity;
		std::ostringstream* m_ssLayer;

	protected:
		void putLine(const Vector3d& s, const Vector3d& e,
			std::ostringstream* outStream, const std::string handle,
			const std::string ownerHandle);
		void putText(const char* text, const Vector3d& location1, const Vector3d& location2,
			const double height, const int horizJust,
			std::ostringstream* outStream, const std::string handle,
			const std::string ownerHandle);
		void putArrow(const Vector3d& arrowPos, const Vector3d& barb1Pos, const Vector3d& barb2Pos,
			std::ostringstream* outStream, const std::string handle,
			const std::string ownerHandle);

		//! copy boiler plate file
		std::string getPlateFile(std::string fileSpec);
		void setDataDir(std::string s) { m_dataDir = s; }
		std::string getHandle(void);
		std::string getEntityHandle(void);
		std::string getLayerHandle(void);
		std::string getBlockHandle(void);
		std::string getBlkRecordHandle(void);

		std::string m_optionSource;
		int m_version;
		int m_handle;
		int m_entityHandle;
		int m_layerHandle;
		int m_blockHandle;
		int m_blkRecordHandle;
		bool m_polyOverride;

		std::string m_saveModelSpaceHandle;
		std::string m_savePaperSpaceHandle;
		std::string m_saveBlockRecordTableHandle;
		std::string m_saveBlkRecordHandle;
		std::string m_currentBlock;
		std::string m_dataDir;
		std::string m_layerName;
		std::vector<std::string> m_layerList;
		std::vector<std::string> m_blockList;
		std::vector<std::string> m_blkRecordList;

	public:
		CDxfWrite(const char* filepath);
		~CDxfWrite();

		void init(void);
		void endRun(void);

		bool Failed() { return m_fail; }
		//    void setOptions(void);
		//    bool isVersionValid(int vers);
		std::string getLayerName() { return m_layerName; }
		void setLayerName(std::string s);
		void setVersion(int v) { m_version = v; }
		void setPolyOverride(bool b) { m_polyOverride = b; }
		void addBlockName(std::string s, std::string blkRecordHandle);

		void writeLine(const Vector3d& s, const Vector3d& e);
		void writePoint(const Vector3d&);
		void writeArc(const Vector3d& s, const Vector3d& e, const Vector3d& c, bool dir);
		void writeEllipse(const Vector3d& c, double major_radius, double minor_radius,
			double rotation, double start_angle, double end_angle, bool endIsCW);
		void writeCircle(const Vector3d& c, double radius);
		void writeSpline(const SplineDataOut& sd);
		void writeLWPolyLine(const LWPolyDataOut& pd);
		void writePolyline(const LWPolyDataOut& pd);
		void writeVertex(double x, double y, double z);
		void writeText(const char* text, const Vector3d& location1, const Vector3d& location2,
			const double height, const int horizJust);
		void writeLinearDim(const Vector3d& textMidPoint, const Vector3d& lineDefPoint,
			const Vector3d& extLine1, const Vector3d& extLine2,
			const char* dimText, int type);
		void writeLinearDimBlock(const Vector3d& textMidPoint, const Vector3d& lineDefPoint,
			const Vector3d& extLine1, const Vector3d& extLine2,
			const char* dimText, int type);
		void writeAngularDim(const Vector3d& textMidPoint, const Vector3d& lineDefPoint,
			const Vector3d& startExt1, const Vector3d& endExt1,
			const Vector3d& startExt2, const Vector3d& endExt2,
			const char* dimText);
		void writeAngularDimBlock(const Vector3d& textMidPoint, const Vector3d& lineDefPoint,
			const Vector3d& startExt1, const Vector3d& endExt1,
			const Vector3d& startExt2, const Vector3d& endExt2,
			const char* dimText);
		void writeRadialDim(const Vector3d& centerPoint, const Vector3d& textMidPoint,
			const Vector3d& arcPoint,
			const char* dimText);
		void writeRadialDimBlock(const Vector3d& centerPoint, const Vector3d& textMidPoint,
			const Vector3d& arcPoint, const char* dimText);
		void writeDiametricDim(const Vector3d& textMidPoint,
			const Vector3d& arcPoint1, const Vector3d& arcPoint2,
			const char* dimText);
		void writeDiametricDimBlock(const Vector3d& textMidPoint,
			const Vector3d& arcPoint1, const Vector3d& arcPoint2,
			const char* dimText);

		void writeDimBlockPreamble();
		void writeBlockTrailer(void);

		void writeHeaderSection(void);
		void writeTablesSection(void);
		void writeBlocksSection(void);
		void writeEntitiesSection(void);
		void writeObjectsSection(void);
		void writeClassesSection(void);

		void makeLayerTable(void);
		void makeBlockRecordTableHead(void);
		void makeBlockRecordTableBody(void);
		void makeBlockSectionHead(void);
	};

	// derive a class from this and implement it's virtual functions
	class CDxfRead {
	private:
		std::ifstream* m_ifs;

		bool m_fail;
		char m_str[1024];
		char m_unused_line[1024];
		eDxfUnits_t m_eUnits;
		bool m_measurement_inch;
		char m_layer_name[1024];
		char m_section_name[1024];
		char m_block_name[1024];
		bool m_ignore_errors;


		typedef std::map< std::string, Aci_t > LayerAciMap_t;
		LayerAciMap_t m_layer_aci;  // layer names -> layer color aci map

		bool ReadUnits();
		bool ReadLayer();
		bool ReadLine();
		bool ReadText();
		bool ReadArc();
		bool ReadCircle();
		bool ReadEllipse();
		bool ReadPoint();
		bool ReadSpline();
		bool ReadLwPolyLine();
		bool ReadPolyLine();
		bool ReadVertex(double* pVertex, bool* bulge_found, double* bulge);
		void OnReadArc(double start_angle, double end_angle, double radius, const Vector3d& c, double z_extrusion_dir, bool hidden);
		void OnReadCircle(const Vector3d& c, double radius, bool hidden);
		void OnReadEllipse(const Vector3d& c, const Vector3d& m, double ratio, double start_angle, double end_angle);
		bool ReadInsert();
		bool ReadDimension();
		bool ReadBlockInfo();

		void get_line();
		void put_line(const char* value);
		void DerefACI();

	protected:
		Aci_t m_aci; // manifest color name or 256 for layer color

	public:
		CDxfRead(const char* filepath); // this opens the file
		virtual ~CDxfRead(); // this closes the file

		bool Failed() { return m_fail; }
		void DoRead(const bool ignore_errors = false); // this reads the file and calls the following functions

		double mm(double value) const;

		bool IgnoreErrors() const { return(m_ignore_errors); }

		virtual void OnReadLine(const Vector3d& /*s*/, const Vector3d& /*e*/, bool /*hidden*/) {}
		virtual void OnReadPoint(const Vector3d& /*s*/) {}
		virtual void OnReadText(const Vector3d& /*point*/, const double /*height*/, const char* /*text*/) {}
		virtual void OnReadArc(const Vector3d& /*s*/, const Vector3d& /*e*/, const Vector3d& /*c*/, bool /*dir*/, bool /*hidden*/) {}
		virtual void OnReadCircle(const Vector3d& /*s*/, const Vector3d& /*c*/, bool /*dir*/, bool /*hidden*/) {}
		virtual void OnReadEllipse(const Vector3d& /*c*/, double /*major_radius*/, double /*minor_radius*/, double /*rotation*/, double /*start_angle*/, double /*end_angle*/, bool /*dir*/) {}
		virtual void OnReadSpline(struct SplineData& /*sd*/) {}
		virtual void OnReadInsert(const Vector3d& /*point*/, const Vector3d& /*scale*/, const char* /*name*/, double /*rotation*/) {}
		virtual void OnReadDimension(const Vector3d& /*s*/, const Vector3d& /*e*/, const Vector3d& /*point*/, double /*rotation*/) {}
		virtual void AddGraphics() const { }

		std::string LayerName() const;

	};
}
