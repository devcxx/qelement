#ifndef EL_SLIDER_H
#define EL_SLIDER_H

#include "el_global.h"
#include <QAbstractSlider>

EL_BEGIN_NAMESPACE

class OverlayWidget : public QWidget {
    Q_OBJECT
public:
    explicit OverlayWidget(QWidget* parent = 0);
    ~OverlayWidget();

protected:
    bool event(QEvent* event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject* obj, QEvent* event) Q_DECL_OVERRIDE;

    virtual QRect overlayGeometry() const;
};

class Slider;
class SliderThumb : public OverlayWidget {
    Q_OBJECT
public:
    explicit SliderThumb(Slider* slider);
    ~SliderThumb();
    void setDiameter(qreal diameter);
    qreal diameter() const;

    void setBorderWidth(qreal width);
    qreal borderWidth() const;

    void setBorderColor(const QColor& color);
    QColor borderColor() const;

    void setFillColor(const QColor& color);
    QColor fillColor() const;

    void setHaloSize(qreal size);
    qreal haloSize() const;

    void setHaloColor(const QColor& color);
    QColor haloColor() const;

    void setOffset(int offset);
    int offset() const;

protected:
    bool eventFilter(QObject* obj, QEvent* event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

private:
    const Slider* const _slider;
    QColor _borderColor;
    QColor _fillColor;
    QColor _haloColor;
    qreal _diameter;
    qreal _borderWidth;
    qreal _haloSize;
    int _offset;
};

class SliderTrack : public OverlayWidget {
    Q_OBJECT
public:
    explicit SliderTrack(SliderThumb* thumb, Slider* slider);
    ~SliderTrack();

    void setFillColor(const QColor& color);
    QColor fillColor() const;

    void setTrackWidth(int width);
    int trackWidth() const;

protected:
    bool eventFilter(QObject* obj, QEvent* event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

private:
    const Slider* const _slider;
    SliderThumb* const _thumb;
    QColor _fillColor;
    int _trackWidth;
};

// Slider 滑块
class Slider : public QAbstractSlider {
    Q_OBJECT
public:
    Slider(QWidget* parent = nullptr);

    void setThumbColor(const QColor& color);
    QColor thumbColor() const;

    void setTrackColor(const QColor& color);
    QColor trackColor() const;

    void setDisabledColor(const QColor& color);
    QColor disabledColor() const;

    void setPageStepMode(bool pageStep);
    bool pageStepMode() const;

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    void setInvertedAppearance(bool value);

protected:
    void sliderChange(SliderChange change) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent* event) Q_DECL_OVERRIDE;

    void updateThumbOffset();

private:
    void init();
    QRectF trackBoundingRect() const;
    QRectF thumbBoundingRect() const;
    int valueFromPosition(const QPoint& pos) const;
    void setHovered(bool status);

private:
    SliderThumb* _thumb;
    SliderTrack* _track;
    QColor _thumbColor;
    QColor _trackColor;
    QColor _disabledColor;
    int _stepTo;
    int _oldValue;
    int _trackWidth;
    bool _hoverTrack;
    bool _hoverThumb;
    bool _hover;
    bool _step;
    bool _pageStepMode;
};

EL_END_NAMESPACE

#endif // EL_SLIDER_H
