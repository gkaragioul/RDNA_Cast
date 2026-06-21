#pragma once

#ifdef OBS_AMD_LITE

#include <QDialog>

#define GK_OBS_LITE_VERSION "0.7.28"
#define GK_OBS_LITE_PRODUCT_NAME "RDNA Cast"
#define GK_OBS_LITE_RELEASES_REPO "gkaragioul/RDNA_Cast"
#define GK_OBS_LITE_RELEASES_URL "https://github.com/gkaragioul/RDNA_Cast/releases/latest"

class GKAboutDialog : public QDialog {
	Q_OBJECT

public:
	explicit GKAboutDialog(QWidget *parent = nullptr);
};

#endif /* OBS_AMD_LITE */
