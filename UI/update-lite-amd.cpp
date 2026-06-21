#ifdef OBS_AMD_LITE

#include "update-lite-amd.hpp"

#include <QByteArray>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QTextBrowser>
#include <QVBoxLayout>

#ifdef _WIN32
#include <windows.h>
#pragma comment(lib, "version.lib")

static QString GetAMFRuntimeVersion()
{
	const char *dllName = "amfrt64.dll";
	DWORD handle = 0;
	DWORD size = GetFileVersionInfoSizeA(dllName, &handle);
	if (size == 0)
		return QString();

	QByteArray buf(static_cast<int>(size), 0);
	if (!GetFileVersionInfoA(dllName, handle, size, buf.data()))
		return QString();

	VS_FIXEDFILEINFO *info = nullptr;
	UINT infoSize = 0;
	if (!VerQueryValueA(buf.constData(), "\\", reinterpret_cast<LPVOID *>(&info), &infoSize) || !info)
		return QString();

	return QStringLiteral("%1.%2.%3.%4")
		.arg(HIWORD(info->dwFileVersionMS))
		.arg(LOWORD(info->dwFileVersionMS))
		.arg(HIWORD(info->dwFileVersionLS))
		.arg(LOWORD(info->dwFileVersionLS));
}
#else
static QString GetAMFRuntimeVersion()
{
	return QString();
}
#endif

GKAboutDialog::GKAboutDialog(QWidget *parent) : QDialog(parent)
{
	setWindowTitle("About RDNA Cast");
	setFixedSize(480, 420);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	auto *layout = new QVBoxLayout(this);

	QString amfVersion = GetAMFRuntimeVersion();
	QString amfLine = amfVersion.isEmpty()
				  ? QStringLiteral("<p><b>AMD AMF runtime:</b> not detected</p>")
				  : QStringLiteral("<p><b>AMD AMF runtime:</b> %1</p>").arg(amfVersion);

	QString titleHtml = QStringLiteral(
				    "<div style='text-align:center;'>"
				    "<h1 style='color:#e63946;'>RDNA Cast</h1>"
				    "<p style='font-size:14px;'>Version " GK_OBS_LITE_VERSION " (64-bit)</p>"
				    "<p>High-performance streaming for AMD Radeon. Gaming unleashed.</p>"
				    "<p><b>Developer:</b> George Karagioules</p>"
				    "<p><b>Based on:</b> OBS Studio 31.0.3 by the OBS Project</p>") +
			    amfLine +
			    QStringLiteral(
				    "<p style='font-size:11px;color:#888;'>Not affiliated with, endorsed by, or sponsored by "
				    "Advanced Micro Devices, Inc. or the OBS Project. &quot;AMD&quot;, &quot;Radeon&quot;, and "
				    "&quot;RDNA&quot; are trademarks of Advanced Micro Devices, Inc.</p>"
				    "<hr>"
				    "</div>");

	auto *titleLabel = new QLabel(titleHtml);
	titleLabel->setWordWrap(true);
	titleLabel->setAlignment(Qt::AlignCenter);
	layout->addWidget(titleLabel);

	auto *eulaLabel = new QLabel("<b>Licenses</b>");
	layout->addWidget(eulaLabel);

	auto *eulaBrowser = new QTextBrowser();
	eulaBrowser->setPlainText(
		"RDNA Cast is an OBS Studio fork. The combined application and "
		"binary distributions are redistributed under the GNU General "
		"Public License version 2.0 or, at your option, any later version "
		"(GPL-2.0-or-later).\n\n"
		"The complete GPL text is included in the installed COPYING file "
		"and in the source repository.\n\n"
		"Original RDNA Cast additions are also offered under the MIT "
		"License by George Karagioules. That MIT grant applies only to "
		"original RDNA Cast additions and does not relicense OBS Studio or "
		"the combined OBS-derived application.\n\n"
		"MIT License - RDNA Cast original additions\n\n"
		"Copyright (c) 2026 George Karagioules\n\n"
		"Permission is hereby granted, free of charge, to any person obtaining a copy "
		"of the original RDNA Cast additions and associated documentation files "
		"(the \"Software\"), to deal in the Software without restriction, including "
		"without limitation the rights to use, copy, modify, merge, publish, "
		"distribute, sublicense, and/or sell copies of the Software, and to permit "
		"persons to whom the Software is furnished to do so, subject to the "
		"following conditions:\n\n"
		"The above copyright notice and this permission notice shall be included in all "
		"copies or substantial portions of the Software.\n\n"
		"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR "
		"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, "
		"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE "
		"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER "
		"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, "
		"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE "
		"SOFTWARE.\n\n"
		"---\n\n"
		"Bundled third-party components retain their own licenses. See "
		"THIRD_PARTY_LICENSES.md installed alongside the application.\n\n"
		"OBS Studio: Copyright (C) Hugh Bailey and contributors.\n"
		"AMD AMF SDK: Copyright (c) Advanced Micro Devices, Inc.\n\n"
		"Updates: " GK_OBS_LITE_RELEASES_URL "\n"
		"Source: https://github.com/gkaragioul/RDNA_Cast");
	eulaBrowser->setReadOnly(true);
	layout->addWidget(eulaBrowser);

	auto *closeButton = new QPushButton("Close");
	closeButton->setDefault(true);

	auto *btnLayout = new QHBoxLayout();
	btnLayout->addStretch();
	btnLayout->addWidget(closeButton);
	layout->addLayout(btnLayout);

	connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
}

#endif /* OBS_AMD_LITE */
