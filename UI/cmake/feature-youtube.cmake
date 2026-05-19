set(_youtube_has_built_in_oauth
    FALSE
)

if(NOT YOUTUBE_CLIENTID_HASH MATCHES "^(0|[a-fA-F0-9]+)$")
  set(YOUTUBE_CLIENTID_HASH 0)
endif()

if(NOT YOUTUBE_SECRET_HASH MATCHES "^(0|[a-fA-F0-9]+)$")
  set(YOUTUBE_SECRET_HASH 0)
endif()

if(
  YOUTUBE_CLIENTID
  AND YOUTUBE_SECRET
  AND YOUTUBE_CLIENTID_HASH MATCHES "^(0|[a-fA-F0-9]+)$"
  AND YOUTUBE_SECRET_HASH MATCHES "^(0|[a-fA-F0-9]+)$"
)
  set(_youtube_has_built_in_oauth TRUE)
endif()

if(TARGET OBS::browser-panels AND (_youtube_has_built_in_oauth OR OBS_AMD_LITE))
  target_sources(
    obs-studio
    PRIVATE
      auth-youtube.cpp
      auth-youtube.hpp
      window-dock-youtube-app.cpp
      window-dock-youtube-app.hpp
      window-youtube-actions.cpp
      window-youtube-actions.hpp
      youtube-api-wrappers.cpp
      youtube-api-wrappers.hpp
  )

  target_enable_feature(obs-studio "YouTube API connection" YOUTUBE_ENABLED)
else()
  target_disable_feature(obs-studio "YouTube API connection")
  set(YOUTUBE_SECRET_HASH 0)
  set(YOUTUBE_CLIENTID_HASH 0)
endif()
