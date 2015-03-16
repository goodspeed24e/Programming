<?php
    include("swmcntdb.php");	
	$sql="UPDATE prty SET prtyname = '$prtyname' WHERE   prtyno = '$prtyno' LIMIT 1";
    mysql_query($sql);	
?>
<script>
location.href = "index.php?$Act=10";
</script>   