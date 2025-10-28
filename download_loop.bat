@echo off
:: Quick YouTube → audio downloader for Rekordbox

:: === EDIT THIS LINE TO YOUR FOLDER ===
set "TARGET=C:\Users\USER\Music\rekordbox\LiveRequests"

:: Default audio format (mp3/m4a/wav/flac)
set "FORMAT=mp3"

:loop
echo.
set /p "URL=Paste YouTube URL (blank to quit): "
if "%URL%"=="" goto end

yt-dlp.exe -x --audio-format %FORMAT% -o "%TARGET%\%%(title)s.%%(ext)s" --add-metadata --embed-thumbnail %URL%


goto loop

:end
echo Bye!
pause
